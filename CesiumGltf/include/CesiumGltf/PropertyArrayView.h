#pragma once

#include "CesiumGltf/PropertyType.h"
#include "getOffsetFromOffsetsBuffer.h"

#include <CesiumUtility/SpanHelper.h>

#include <gsl/span>

#include <cassert>
#include <cstddef>
#include <variant>
#include <vector>

namespace CesiumGltf {
/**
 * @brief A view on an array element of a {@link PropertyTableProperty}
 * or {@link PropertyTextureProperty}.
 *
 * Provides utility to retrieve the data stored in the array of
 * elements via the array index operator.
 */
template <typename ElementType> class PropertyArrayView {
public:
  /**
   * @brief Constructs an empty array view.
   */
  PropertyArrayView() : _values{} {}

  /**
   * @brief Constructs an array view from a buffer.
   *
   * @param buffer The buffer containing the values.
   */
  PropertyArrayView(const gsl::span<const std::byte>& buffer) noexcept
      : _values{CesiumUtility::reintepretCastSpan<const ElementType>(buffer)} {}

  /**
   * @brief Constructs an array view from a vector of values. This is mainly
   * used when the values cannot be viewed in place.
   *
   * @param values The vector containing the values.
   */
  PropertyArrayView(const std::vector<ElementType>&& values)
      : _values{std::move(values)} {}

  const ElementType& operator[](int64_t index) const noexcept {
    return std::visit(
        [index](auto const& values) -> auto const& { return values[index]; },
        _values);
  }

  int64_t size() const noexcept {
    return std::visit(
        [](auto const& values) { return static_cast<int64_t>(values.size()); },
        _values);
  }

  bool operator==(const PropertyArrayView<ElementType>& other) const noexcept {
    for (int64_t i = 0; i < size(); i++) {
      if ((*this)[i] != other[i]) {
        return false;
      }
    }

    return true;
  }

  PropertyArrayView<ElementType>
  operator*(const PropertyArrayView<ElementType>& other) {
    int64_t clampedSize = std::min(this->size(), other.size());
    std::vector<ElementType> result(static_cast<size_t>(this->size()));
    if constexpr (IsMetadataMatN<ElementType>::value) {
      // Do component-wise multiplication instead of actual matrix
      // multiplication.
      ElementType matN;
      constexpr glm::length_t N = ElementType::length();
      for (int64_t i = 0; i < clampedSize; i++) {
        for (glm::length_t j = 0; j < N; j++) {
          matN[j] = (*this)[i][j] * other[i][j];
        }
        result[i] = matN;
      }
    } else {
      for (int64_t i = 0; i < clampedSize; i++) {
        result[i] = (*this)[i] * other[i];
      }
    }

    // Copy anything that didn't have a component to multiply against.
    for (int64_t i = clampedSize(); i < this->size(); i++) {
      result[i] = (*this)[i];
    }

    return PropertyArrayView<ElementType>(std::move(result));
  }

  PropertyArrayView<ElementType>
  operator+(const PropertyArrayView<ElementType>& other) {
    int64_t clampedSize = std::min(this->size(), other.size());
    std::vector<ElementType> result(static_cast<size_t>(this->size()));
    for (int64_t i = 0; i < clampedSize; i++) {
      result[i] = (*this)[i] + other[i];
    }

    // Copy anything that didn't have a component to multiply against.
    for (int64_t i = clampedSize(); i < this->size(); i++) {
      result[i] = (*this)[i];
    }

    return PropertyArrayView<ElementType>(std::move(result));
  }

private:
  using ArrayType =
      std::variant<gsl::span<const ElementType>, std::vector<ElementType>>;
  ArrayType _values;
};

template <> class PropertyArrayView<bool> {
public:
  /**
   * @brief Constructs an empty array view.
   */
  PropertyArrayView() : _values{} {}

  /**
   * @brief Constructs an array view from a buffer.
   *
   * @param buffer The buffer containing the values.
   * @param bitOffset The offset into the buffer where the values actually
   * begin.
   * @param size The number of values in the array.
   */
  PropertyArrayView(
      const gsl::span<const std::byte>& buffer,
      int64_t bitOffset,
      int64_t size) noexcept
      : _values{buffer}, _bitOffset{bitOffset}, _size{size} {}

  bool operator[](int64_t index) const noexcept {
    index += _bitOffset;
    const int64_t byteIndex = index / 8;
    const int64_t bitIndex = index % 8;
    const int bitValue = static_cast<int>(_values[byteIndex] >> bitIndex) & 1;
    return bitValue == 1;
  }

  int64_t size() const noexcept { return _size; }

  bool operator==(const PropertyArrayView<bool>& other) const noexcept {
    for (int64_t i = 0; i < size(); i++) {
      if ((*this)[i] != other[i]) {
        return false;
      }
    }

    return true;
  }

private:
  gsl::span<const std::byte> _values;
  int64_t _bitOffset = 0;
  int64_t _size = 0;
};

template <> class PropertyArrayView<std::string_view> {
public:
  /**
   * @brief Constructs an empty array view.
   */
  PropertyArrayView()
      : _values{},
        _stringOffsets{},
        _stringOffsetType{PropertyComponentType::None},
        _size{0} {}

  /**
   * @brief Constructs an array view from buffers and their information.
   *
   * @param values The buffer containing the values.
   * @param stringOffsets The buffer containing the string offsets.
   * @param stringOffsetType The component type of the string offsets.
   * @param size The number of values in the array.
   */
  PropertyArrayView(
      const gsl::span<const std::byte>& values,
      const gsl::span<const std::byte>& stringOffsets,
      PropertyComponentType stringOffsetType,
      int64_t size) noexcept
      : _values{values},
        _stringOffsets{stringOffsets},
        _stringOffsetType{stringOffsetType},
        _size(size) {}

  std::string_view operator[](int64_t index) const noexcept {
    const size_t currentOffset =
        getOffsetFromOffsetsBuffer(index, _stringOffsets, _stringOffsetType);
    const size_t nextOffset = getOffsetFromOffsetsBuffer(
        index + 1,
        _stringOffsets,
        _stringOffsetType);
    return std::string_view(
        reinterpret_cast<const char*>(_values.data() + currentOffset),
        (nextOffset - currentOffset));
  }

  int64_t size() const noexcept { return _size; }

  bool
  operator==(const PropertyArrayView<std::string_view>& other) const noexcept {
    for (int64_t i = 0; i < size(); i++) {
      if ((*this)[i] != other[i]) {
        return false;
      }
    }

    return true;
  }

private:
  gsl::span<const std::byte> _values;
  gsl::span<const std::byte> _stringOffsets;
  PropertyComponentType _stringOffsetType;
  int64_t _size;
};
} // namespace CesiumGltf

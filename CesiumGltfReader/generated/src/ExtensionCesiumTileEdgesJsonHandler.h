// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include <CesiumGltf/ExtensionCesiumTileEdges.h>
#include <CesiumJsonReader/ExtensibleObjectJsonHandler.h>
#include <CesiumJsonReader/IntegerJsonHandler.h>

namespace CesiumJsonReader {
class JsonReaderOptions;
} // namespace CesiumJsonReader

namespace CesiumGltfReader {
class ExtensionCesiumTileEdgesJsonHandler
    : public CesiumJsonReader::ExtensibleObjectJsonHandler,
      public CesiumJsonReader::IExtensionJsonHandler {
public:
  using ValueType = CesiumGltf::ExtensionCesiumTileEdges;

  static constexpr const char* ExtensionName = "CESIUM_tile_edges";

  explicit ExtensionCesiumTileEdgesJsonHandler(
      const CesiumJsonReader::JsonReaderOptions& options) noexcept;
  void reset(
      IJsonHandler* pParentHandler,
      CesiumGltf::ExtensionCesiumTileEdges* pObject);

  IJsonHandler* readObjectKey(const std::string_view& str) override;

  void reset(
      IJsonHandler* pParentHandler,
      CesiumUtility::ExtensibleObject& o,
      const std::string_view& extensionName) override;

  IJsonHandler& getHandler() override { return *this; }

protected:
  IJsonHandler* readObjectKeyExtensionCesiumTileEdges(
      const std::string& objectType,
      const std::string_view& str,
      CesiumGltf::ExtensionCesiumTileEdges& o);

private:
  CesiumGltf::ExtensionCesiumTileEdges* _pObject = nullptr;
  CesiumJsonReader::IntegerJsonHandler<int32_t> _left;
  CesiumJsonReader::IntegerJsonHandler<int32_t> _bottom;
  CesiumJsonReader::IntegerJsonHandler<int32_t> _right;
  CesiumJsonReader::IntegerJsonHandler<int32_t> _top;
};
} // namespace CesiumGltfReader

// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "NamedObjectJsonHandler.h"

#include <CesiumGltf/ExtensionModelKhrMaterialsVariantsValue.h>
#include <CesiumJsonReader/StringJsonHandler.h>

namespace CesiumJsonReader {
class JsonReaderOptions;
} // namespace CesiumJsonReader

namespace CesiumGltfReader {
class ExtensionModelKhrMaterialsVariantsValueJsonHandler
    : public CesiumGltfReader::NamedObjectJsonHandler {
public:
  using ValueType = CesiumGltf::ExtensionModelKhrMaterialsVariantsValue;

  explicit ExtensionModelKhrMaterialsVariantsValueJsonHandler(
      const CesiumJsonReader::JsonReaderOptions& options) noexcept;
  void reset(
      IJsonHandler* pParentHandler,
      CesiumGltf::ExtensionModelKhrMaterialsVariantsValue* pObject);

  IJsonHandler* readObjectKey(const std::string_view& str) override;

protected:
  IJsonHandler* readObjectKeyExtensionModelKhrMaterialsVariantsValue(
      const std::string& objectType,
      const std::string_view& str,
      CesiumGltf::ExtensionModelKhrMaterialsVariantsValue& o);

private:
  CesiumGltf::ExtensionModelKhrMaterialsVariantsValue* _pObject = nullptr;
  CesiumJsonReader::StringJsonHandler _name;
};
} // namespace CesiumGltfReader

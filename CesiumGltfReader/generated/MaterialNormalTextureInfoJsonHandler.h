// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "DoubleJsonHandler.h"
#include "TextureInfoJsonHandler.h"
#include <CesiumGltf/Reader.h>

namespace CesiumGltf {
struct MaterialNormalTextureInfo;

class MaterialNormalTextureInfoJsonHandler : public TextureInfoJsonHandler {
public:
  MaterialNormalTextureInfoJsonHandler(const ReaderContext& context) noexcept;
  void reset(IJsonReader* pHandler, MaterialNormalTextureInfo* pObject);
  MaterialNormalTextureInfo* getObject();
  virtual void reportWarning(
      const std::string& warning,
      std::vector<std::string>&& context = std::vector<std::string>()) override;

  virtual IJsonReader* readObjectKey(const std::string_view& str) override;

protected:
  IJsonReader* readObjectKeyMaterialNormalTextureInfo(
      const std::string& objectType,
      const std::string_view& str,
      MaterialNormalTextureInfo& o);

private:
  MaterialNormalTextureInfo* _pObject = nullptr;
  DoubleJsonHandler _scale;
};
} // namespace CesiumGltf

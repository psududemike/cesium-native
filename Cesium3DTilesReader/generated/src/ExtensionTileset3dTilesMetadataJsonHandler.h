// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "GroupMetadataJsonHandler.h"
#include "SchemaJsonHandler.h"
#include "StatisticsJsonHandler.h"
#include "TilesetMetadataJsonHandler.h"

#include <Cesium3DTiles/ExtensionTileset3dTilesMetadata.h>
#include <CesiumJsonReader/ArrayJsonHandler.h>
#include <CesiumJsonReader/ExtensibleObjectJsonHandler.h>
#include <CesiumJsonReader/StringJsonHandler.h>

namespace CesiumJsonReader {
class ExtensionReaderContext;
}

namespace Cesium3DTilesReader {
class ExtensionTileset3dTilesMetadataJsonHandler
    : public CesiumJsonReader::ExtensibleObjectJsonHandler,
      public CesiumJsonReader::IExtensionJsonHandler {
public:
  using ValueType = Cesium3DTiles::ExtensionTileset3dTilesMetadata;

  static inline constexpr const char* ExtensionName = "3DTILES_metadata";

  ExtensionTileset3dTilesMetadataJsonHandler(
      const CesiumJsonReader::ExtensionReaderContext& context) noexcept;
  void reset(
      IJsonHandler* pParentHandler,
      Cesium3DTiles::ExtensionTileset3dTilesMetadata* pObject);

  virtual IJsonHandler* readObjectKey(const std::string_view& str) override;

  virtual void reset(
      IJsonHandler* pParentHandler,
      CesiumUtility::ExtensibleObject& o,
      const std::string_view& extensionName) override;

  virtual IJsonHandler* readNull() override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readNull();
  };
  virtual IJsonHandler* readBool(bool b) override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readBool(b);
  }
  virtual IJsonHandler* readInt32(int32_t i) override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readInt32(i);
  }
  virtual IJsonHandler* readUint32(uint32_t i) override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readUint32(i);
  }
  virtual IJsonHandler* readInt64(int64_t i) override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readInt64(i);
  }
  virtual IJsonHandler* readUint64(uint64_t i) override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readUint64(i);
  }
  virtual IJsonHandler* readDouble(double d) override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readDouble(d);
  }
  virtual IJsonHandler* readString(const std::string_view& str) override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readString(str);
  }
  virtual IJsonHandler* readObjectStart() override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readObjectStart();
  }
  virtual IJsonHandler* readObjectEnd() override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readObjectEnd();
  }
  virtual IJsonHandler* readArrayStart() override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readArrayStart();
  }
  virtual IJsonHandler* readArrayEnd() override {
    return CesiumJsonReader::ExtensibleObjectJsonHandler::readArrayEnd();
  }
  virtual void reportWarning(
      const std::string& warning,
      std::vector<std::string>&& context =
          std::vector<std::string>()) override {
    CesiumJsonReader::ExtensibleObjectJsonHandler::reportWarning(
        warning,
        std::move(context));
  }

protected:
  IJsonHandler* readObjectKeyExtensionTileset3dTilesMetadata(
      const std::string& objectType,
      const std::string_view& str,
      Cesium3DTiles::ExtensionTileset3dTilesMetadata& o);

private:
  Cesium3DTiles::ExtensionTileset3dTilesMetadata* _pObject = nullptr;
  SchemaJsonHandler _schema;
  CesiumJsonReader::StringJsonHandler _schemaUri;
  StatisticsJsonHandler _statistics;
  CesiumJsonReader::
      ArrayJsonHandler<Cesium3DTiles::GroupMetadata, GroupMetadataJsonHandler>
          _groups;
  TilesetMetadataJsonHandler _tileset;
};
} // namespace Cesium3DTilesReader

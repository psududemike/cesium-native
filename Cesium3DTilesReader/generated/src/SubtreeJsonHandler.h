// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "AvailabilityJsonHandler.h"
#include "BufferJsonHandler.h"
#include "BufferViewJsonHandler.h"
#include "MetadataEntityJsonHandler.h"
#include "PropertyTableJsonHandler.h"

#include <Cesium3DTiles/Subtree.h>
#include <CesiumJsonReader/ArrayJsonHandler.h>
#include <CesiumJsonReader/ExtensibleObjectJsonHandler.h>
#include <CesiumJsonReader/IntegerJsonHandler.h>

namespace CesiumJsonReader {
class ExtensionReaderContext;
}

namespace Cesium3DTilesReader {
class SubtreeJsonHandler
    : public CesiumJsonReader::ExtensibleObjectJsonHandler {
public:
  using ValueType = Cesium3DTiles::Subtree;

  SubtreeJsonHandler(
      const CesiumJsonReader::ExtensionReaderContext& context) noexcept;
  void reset(IJsonHandler* pParentHandler, Cesium3DTiles::Subtree* pObject);

  virtual IJsonHandler* readObjectKey(const std::string_view& str) override;

protected:
  IJsonHandler* readObjectKeySubtree(
      const std::string& objectType,
      const std::string_view& str,
      Cesium3DTiles::Subtree& o);

private:
  Cesium3DTiles::Subtree* _pObject = nullptr;
  CesiumJsonReader::ArrayJsonHandler<Cesium3DTiles::Buffer, BufferJsonHandler>
      _buffers;
  CesiumJsonReader::
      ArrayJsonHandler<Cesium3DTiles::BufferView, BufferViewJsonHandler>
          _bufferViews;
  CesiumJsonReader::
      ArrayJsonHandler<Cesium3DTiles::PropertyTable, PropertyTableJsonHandler>
          _propertyTables;
  AvailabilityJsonHandler _tileAvailability;
  CesiumJsonReader::
      ArrayJsonHandler<Cesium3DTiles::Availability, AvailabilityJsonHandler>
          _contentAvailability;
  AvailabilityJsonHandler _childSubtreeAvailability;
  CesiumJsonReader::IntegerJsonHandler<int64_t> _tileMetadata;
  CesiumJsonReader::
      ArrayJsonHandler<int64_t, CesiumJsonReader::IntegerJsonHandler<int64_t>>
          _contentMetadata;
  MetadataEntityJsonHandler _subtreeMetadata;
};
} // namespace Cesium3DTilesReader

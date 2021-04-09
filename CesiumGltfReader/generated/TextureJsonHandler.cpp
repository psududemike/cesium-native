// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "TextureJsonHandler.h"
#include "CesiumGltf/Texture.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

TextureJsonHandler::TextureJsonHandler(const ReaderContext& context) noexcept
    : NamedObjectJsonHandler(context), _sampler(context), _source(context) {}

void TextureJsonHandler::reset(IJsonReader* pParent, Texture* pObject) {
  NamedObjectJsonHandler::reset(pParent, pObject);
  this->_pObject = pObject;
}

Texture* TextureJsonHandler::getObject() { return this->_pObject; }

void TextureJsonHandler::reportWarning(
    const std::string& warning,
    std::vector<std::string>&& context) {
  if (this->getCurrentKey()) {
    context.emplace_back(std::string(".") + this->getCurrentKey());
  }
  this->parent()->reportWarning(warning, std::move(context));
}

IJsonReader* TextureJsonHandler::readObjectKey(const std::string_view& str) {
  assert(this->_pObject);
  return this->readObjectKeyTexture(Texture::TypeName, str, *this->_pObject);
}

IJsonReader* TextureJsonHandler::readObjectKeyTexture(
    const std::string& objectType,
    const std::string_view& str,
    Texture& o) {
  using namespace std::string_literals;

  if ("sampler"s == str)
    return property("sampler", this->_sampler, o.sampler);
  if ("source"s == str)
    return property("source", this->_source, o.source);

  return this->readObjectKeyNamedObject(objectType, str, *this->_pObject);
}

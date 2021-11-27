// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <ArduinoJson/Polyfills/assert.hpp>
#include <ArduinoJson/Variant/VariantData.hpp>

namespace ARDUINOJSON_NAMESPACE {

struct SlotKeySetter {
  SlotKeySetter(VariantSlot* instance) : _instance(instance) {}

  template <typename TStoredString>
  bool operator()(TStoredString s) {
    if (!s)
      return false;
    ARDUINOJSON_ASSERT(_instance != 0);
    _instance->setKey(s);
    return true;
  }

  VariantSlot* _instance;
};

template <typename TAdaptedString, typename TStoragePolicy>
inline bool slotSetKey(VariantSlot* var, TAdaptedString key,
                       TStoragePolicy storage) {
  return storage.store(key, SlotKeySetter(var));
}

inline size_t slotSize(const VariantSlot* var) {
  size_t n = 0;
  while (var) {
    n++;
    var = var->next();
  }
  return n;
}

inline VariantData* slotData(VariantSlot* slot) {
  return reinterpret_cast<VariantData*>(slot);
}
}  // namespace ARDUINOJSON_NAMESPACE

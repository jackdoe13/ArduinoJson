// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <ArduinoJson/Memory/MemoryPool.hpp>
#include <ArduinoJson/Strings/StoredString.hpp>
#include <ArduinoJson/Strings/String.hpp>

namespace ARDUINOJSON_NAMESPACE {

namespace storage_policies {
class store_by_address {
 public:
  template <typename TAdaptedString, typename TCallback>
  bool store(TAdaptedString str, TCallback callback) {
    return callback(LinkedString(str.data(), str.size()));
  }
};

class store_by_copy {
 public:
  store_by_copy(MemoryPool *pool) : _pool(pool) {}

  template <typename TAdaptedString, typename TCallback>
  bool store(TAdaptedString str, TCallback callback);

 private:
  MemoryPool *_pool;
};

class decide_at_runtime : store_by_address, store_by_copy {
 public:
  decide_at_runtime(MemoryPool *pool, bool isStatic)
      : store_by_copy(pool), _isStatic(isStatic) {}

  template <typename TAdaptedString, typename TCallback>
  bool store(TAdaptedString str, TCallback callback) {
    if (_isStatic)
      return store_by_address::store(str, callback);
    else
      return store_by_copy::store(str, callback);
  }

 private:
  bool _isStatic;
};
}  // namespace storage_policies

template <typename T>
inline storage_policies::store_by_copy getStoragePolicy(const T &,
                                                        MemoryPool *pool) {
  return storage_policies::store_by_copy(pool);
}

inline storage_policies::store_by_address getStoragePolicy(const char *,
                                                           MemoryPool *) {
  return storage_policies::store_by_address();
}

inline storage_policies::decide_at_runtime getStoragePolicy(const String &s,
                                                            MemoryPool *pool) {
  return storage_policies::decide_at_runtime(pool, s.isStatic());
}

}  // namespace ARDUINOJSON_NAMESPACE

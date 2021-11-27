// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <ArduinoJson/Memory/MemoryPool.hpp>
#include <ArduinoJson/Strings/StoredString.hpp>
#include <ArduinoJson/Strings/String.hpp>

namespace ARDUINOJSON_NAMESPACE {

namespace storage_policies {
// TODO: memory pool as a member?
struct store_by_address {
  template <typename TAdaptedString, typename TCallback>
  bool store(TAdaptedString str, MemoryPool *,
             TCallback callback) {  // TODO: test pass by ref
    return callback(LinkedString(str.data(), str.size()));
  }
};

struct store_by_copy {
  typedef CopiedString TResult;

  template <typename TAdaptedString, typename TCallback>
  bool store(TAdaptedString str, MemoryPool *pool, TCallback callback);
};

struct decide_at_runtime : private store_by_address, store_by_copy {
  decide_at_runtime(bool x) : store_by_address(x) {}
  bool store_by_address;

  template <typename TAdaptedString, typename TCallback>
  bool store(TAdaptedString str, MemoryPool *pool,
             TCallback callback) {  // TODO: test pass by ref
    if (store_by_address)
      return store_by_address::store(str, pool, callback);
    else
      return store_by_copy::store(str, pool, callback);
  }
};
}  // namespace storage_policies

template <typename T>
inline storage_policies::store_by_copy getStoragePolicy(const T &) {
  return storage_policies::store_by_copy();
}

inline storage_policies::store_by_address getStoragePolicy(const char *) {
  return storage_policies::store_by_address();
}

inline storage_policies::decide_at_runtime getStoragePolicy(const String &s) {
  return storage_policies::decide_at_runtime(s.isStatic());
}

}  // namespace ARDUINOJSON_NAMESPACE

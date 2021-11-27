// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <ArduinoJson/Strings/String.hpp>

namespace ARDUINOJSON_NAMESPACE {

namespace storage_policies {
struct store_by_address {};
struct store_by_copy {};
struct decide_at_runtime {
  decide_at_runtime(bool x) : store_by_address(x) {}
  bool store_by_address;
};
}  // namespace storage_policies

template <typename T>
inline storage_policies::store_by_copy getStoragePolicy(const T&) {
  return storage_policies::store_by_copy();
}

inline storage_policies::store_by_address getStoragePolicy(const char*) {
  return storage_policies::store_by_address();
}

}  // namespace ARDUINOJSON_NAMESPACE

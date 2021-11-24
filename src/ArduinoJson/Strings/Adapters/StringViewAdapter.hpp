// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <ArduinoJson/Strings/Adapters/RamStringAdapter.hpp>

#include <string_view>

namespace ARDUINOJSON_NAMESPACE {

inline RamStringAdapter adaptString(const std::string& s) {
  return RamStringAdapter(s.data(), s.size());
}

template <>
struct IsString<std::string_view> : true_type {};

}  // namespace ARDUINOJSON_NAMESPACE

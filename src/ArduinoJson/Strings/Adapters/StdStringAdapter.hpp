// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <ArduinoJson/Strings/Adapters/RamStringAdapter.hpp>

#include <string>

namespace ARDUINOJSON_NAMESPACE {

inline RamStringAdapter adaptString(const std::string& s) {
  return RamStringAdapter(s.c_str(), s.size());
}

template <>
struct IsString<std::string> : true_type {};

}  // namespace ARDUINOJSON_NAMESPACE

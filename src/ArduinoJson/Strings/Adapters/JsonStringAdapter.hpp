// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <ArduinoJson/Strings/Adapters/RamStringAdapter.hpp>
#include <ArduinoJson/Strings/IsString.hpp>
#include <ArduinoJson/Strings/String.hpp>

namespace ARDUINOJSON_NAMESPACE {

inline RamStringAdapter adaptString(const String& s) {
  return RamStringAdapter(s.c_str(), s.size());
}

template <>
struct IsString<String> : true_type {};

}  // namespace ARDUINOJSON_NAMESPACE

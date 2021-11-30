// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <stddef.h>  // size_t
#include <string.h>  // strcmp

#include <ArduinoJson/Polyfills/assert.hpp>
#include <ArduinoJson/Polyfills/safe_strcmp.hpp>
#include <ArduinoJson/Strings/IsString.hpp>

namespace ARDUINOJSON_NAMESPACE {

class ZeroTerminatedRamString {
 public:
  ZeroTerminatedRamString(const char* str) : _str(str) {}

  bool isNull() const {
    return !_str;
  }

  size_t size() const {
    return _str ? ::strlen(_str) : 0;
  }

  char operator[](size_t i) const {
    ARDUINOJSON_ASSERT(_str != 0);
    ARDUINOJSON_ASSERT(i <= size());
    return _str[i];
  }

  const char* data() const {
    return _str;
  }

 protected:
  const char* _str;
};

class SizedRamString {
 public:
  SizedRamString(const char* str, size_t sz) : _str(str), _size(sz) {}

  bool isNull() const {
    return !_str;
  }

  size_t size() const {
    return _size;
  }

  char operator[](size_t i) const {
    ARDUINOJSON_ASSERT(_str != 0);
    ARDUINOJSON_ASSERT(i <= size());
    return _str[i];
  }

  const char* data() const {
    return _str;
  }

 protected:
  const char* _str;
  size_t _size;
};

template <>
struct IsString<char*> : true_type {};

inline ZeroTerminatedRamString adaptString(const char* s) {
  return ZeroTerminatedRamString(s);
}

inline SizedRamString adaptString(const char* s, size_t n) {
  return SizedRamString(s, n);
}

template <int N>
struct IsString<char[N]> : true_type {};

template <int N>
struct IsString<const char[N]> : true_type {};

template <int N>
inline SizedRamString adaptString(char s[N]) {
  return SizedRamString(s, strlen(s));
}

template <>
struct IsString<unsigned char*> : true_type {};

inline ZeroTerminatedRamString adaptString(const unsigned char* s) {
  return adaptString(reinterpret_cast<const char*>(s));
}

template <>
struct IsString<signed char*> : true_type {};

inline ZeroTerminatedRamString adaptString(const signed char* s) {
  return adaptString(reinterpret_cast<const char*>(s));
}
}  // namespace ARDUINOJSON_NAMESPACE

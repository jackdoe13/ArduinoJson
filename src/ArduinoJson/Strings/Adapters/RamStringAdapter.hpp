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

class ZeroTerminatedRamStringAdapter {
 public:
  ZeroTerminatedRamStringAdapter(const char* str) : _str(str) {}

  bool isNull() const {
    return !_str;
  }

  size_t size() const {
    return ::strlen(_str);
  }

  char operator[](size_t i) const {
    ARDUINOJSON_ASSERT(_str != 0);
    ARDUINOJSON_ASSERT(i <= size());
    return _str[i];
  }

  const char* data() const {
    return _str;
  }

  void copyTo(char* p, size_t n) const {
    memcpy(p, _str, n);
  }

 protected:
  const char* _str;
};

class SizedRamStringAdapter {
 public:
  SizedRamStringAdapter(const char* str, size_t sz) : _str(str), _size(sz) {}

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

  void copyTo(char* p, size_t n) const {
    memcpy(p, _str, n);
  }

 protected:
  const char* _str;
  size_t _size;
};

template <>
struct IsString<char*> : true_type {};

inline ZeroTerminatedRamStringAdapter adaptString(const char* s) {
  return ZeroTerminatedRamStringAdapter(s);
}

inline SizedRamStringAdapter adaptString(const char* s, size_t n) {
  return SizedRamStringAdapter(s, n);
}

template <int N>
struct IsString<char[N]> : true_type {};

template <int N>
struct IsString<const char[N]> : true_type {};

template <int N>
inline SizedRamStringAdapter adaptString(char s[N]) {
  return SizedRamStringAdapter(s, strlen(s));
}

template <>
struct IsString<unsigned char*> : true_type {};

inline ZeroTerminatedRamStringAdapter adaptString(const unsigned char* s) {
  return adaptString(reinterpret_cast<const char*>(s));
}

template <>
struct IsString<signed char*> : true_type {};

inline ZeroTerminatedRamStringAdapter adaptString(const signed char* s) {
  return adaptString(reinterpret_cast<const char*>(s));
}
}  // namespace ARDUINOJSON_NAMESPACE

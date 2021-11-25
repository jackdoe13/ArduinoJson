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

class RamStringAdapter {
 public:
  RamStringAdapter() : _str(0), _size(0) {}
  RamStringAdapter(const char* str, size_t sz) : _str(str), _size(sz) {}

  int compare(const char* other) const {
    return safe_strcmp(_str, other);
  }

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
struct IsString<const char*> : true_type {};

template <>
struct IsString<char*> : true_type {};

inline RamStringAdapter adaptString(const char* s) {
  return RamStringAdapter(s, s ? strlen(s) : 0);
}

inline RamStringAdapter adaptString(const char* s, size_t n) {
  return RamStringAdapter(s, n);
}

template <int N>
struct IsString<char[N]> : true_type {};

template <int N>
inline RamStringAdapter adaptString(char s[N]) {
  return RamStringAdapter(s, strlen(s));
}

template <>
struct IsString<unsigned char*> : true_type {};

inline RamStringAdapter adaptString(const unsigned char* s) {
  return adaptString(reinterpret_cast<const char*>(s));
}

template <>
struct IsString<signed char*> : true_type {};

inline RamStringAdapter adaptString(const signed char* s) {
  return adaptString(reinterpret_cast<const char*>(s));
}
}  // namespace ARDUINOJSON_NAMESPACE

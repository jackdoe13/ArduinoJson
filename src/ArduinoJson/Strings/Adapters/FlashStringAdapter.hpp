// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <Arduino.h>

#include <ArduinoJson/Strings/IsString.hpp>

namespace ARDUINOJSON_NAMESPACE {

class FlashStringAdapter {
 public:
  FlashStringAdapter(const __FlashStringHelper* str, size_t sz)
      : _str(str), _size(sz) {}

  int compare(const char* other) const {
    if (!other && !_str)
      return 0;
    if (!_str)
      return -1;
    if (!other)
      return 1;
    return -strncmp_P(other, reinterpret_cast<const char*>(_str), _size);
  }

  bool isNull() const {
    return !_str;
  }

  void copyTo(char* p, size_t n) const {
    memcpy_P(p, reinterpret_cast<const char*>(_str), n);
  }

  char operator[](size_t i) const {
    ARDUINOJSON_ASSERT(_str != 0);
    ARDUINOJSON_ASSERT(i <= _size);
    return static_cast<char>(
        pgm_read_byte(reinterpret_cast<const char*>(_str) + i));
  }

  size_t size() const {
    return _size;
  }

 private:
  const __FlashStringHelper* _str;
  size_t _size;
};

inline FlashStringAdapter adaptString(const __FlashStringHelper* s) {
  return FlashStringAdapter(s,
                            s ? strlen_P(reinterpret_cast<const char*>(s)) : 0);
}

inline FlashStringAdapter adaptString(const __FlashStringHelper* s, size_t n) {
  return FlashStringAdapter(s, n);
}

template <>
struct IsString<const __FlashStringHelper*> : true_type {};

}  // namespace ARDUINOJSON_NAMESPACE

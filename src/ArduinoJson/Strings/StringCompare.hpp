// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <stddef.h>  // size_t

namespace ARDUINOJSON_NAMESPACE {

// TODO: test in isolation
template <typename TAdaptedString>
bool stringEquals(TAdaptedString a, const char* b, size_t n) {
  if (a.isNull() && !b)  // TODO: replace with assert
    return true;
  if (a.isNull() || !b)  // TODO: replace with assert
    return false;
  if (a.size() != n)
    return false;
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

template <typename TAdaptedString>
bool stringEquals(TAdaptedString a, const char* b) {
  // TODO: implement a second version
  return stringEquals(a, b, strlen(b));
}

// TODO: test in isolation
template <typename TAdaptedString>
int stringCompare(TAdaptedString a, const char* b, size_t blen) {
  if (a.isNull() && !b)  // TODO: replace with assert
    return 0;
  if (a.isNull())  // TODO: replace with assert
    return -1;
  if (!b)  // TODO: replace with assert
    return 1;
  size_t alen = a.size();
  size_t n = alen < blen ? alen : blen;
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i])
      return a[i] - b[i];
  }
  if (alen > blen)
    return 1;
  if (alen < blen)
    return -1;
  return 0;
}

}  // namespace ARDUINOJSON_NAMESPACE

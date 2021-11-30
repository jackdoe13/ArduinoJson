// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#define ARDUINOJSON_ENABLE_PROGMEM 1
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#include "custom_string.hpp"
#include "progmem_emulation.hpp"
#include "weird_strcmp.hpp"

#include <ArduinoJson/Strings/StringAdapters.hpp>
#include <ArduinoJson/Strings/StringCompare.hpp>

#include <catch.hpp>

using namespace ARDUINOJSON_NAMESPACE;

TEST_CASE("const char*") {
  SECTION("null") {
    ZeroTerminatedRamString s = adaptString(static_cast<const char*>(0));

    CHECK(s.isNull() == true);
    CHECK(s.size() == 0);
  }

  SECTION("non-null") {
    ZeroTerminatedRamString s = adaptString("bravo");

    CHECK(stringCompare(s, "alpha", 5) > 0);
    CHECK(stringCompare(s, "bravo", 5) == 0);
    CHECK(stringCompare(s, "charlie", 7) < 0);

    CHECK(s.isNull() == false);
    CHECK(s.size() == 5);
  }
}

TEST_CASE("const char* + size") {
  SECTION("null") {
    SizedRamString s = adaptString(static_cast<const char*>(0), 10);

    CHECK(s.isNull() == true);
  }

  SECTION("non-null") {
    SizedRamString s = adaptString("bravo", 5);

    CHECK(stringCompare(s, "alpha", 5) > 0);
    CHECK(stringCompare(s, "bravo", 5) == 0);
    CHECK(stringCompare(s, "charlie", 7) < 0);

    CHECK(s.isNull() == false);
    CHECK(s.size() == 5);
  }
}

TEST_CASE("const __FlashStringHelper*") {
  SECTION("null") {
    FlashStringAdapter s =
        adaptString(static_cast<const __FlashStringHelper*>(0));

    CHECK(s.isNull() == true);
    CHECK(s.size() == 0);
  }

  SECTION("non-null") {
    FlashStringAdapter s = adaptString(F("bravo"));

    CHECK(stringCompare(s, "alpha", 5) > 0);
    CHECK(stringCompare(s, "bravo", 5) == 0);
    CHECK(stringCompare(s, "charlie", 7) < 0);

    CHECK(s.isNull() == false);
    CHECK(s.size() == 5);
  }
}

TEST_CASE("std::string") {
  std::string orig("bravo");
  SizedRamString s = adaptString(orig);

  CHECK(stringCompare(s, "alpha", 5) > 0);
  CHECK(stringCompare(s, "bravo", 5) == 0);
  CHECK(stringCompare(s, "charlie", 7) < 0);

  CHECK(s.isNull() == false);
  CHECK(s.size() == 5);
}

TEST_CASE("Arduino String") {
  ::String orig("bravo");
  SizedRamString s = adaptString(orig);

  CHECK(stringCompare(s, "alpha", 5) > 0);
  CHECK(stringCompare(s, "bravo", 5) == 0);
  CHECK(stringCompare(s, "charlie", 7) < 0);

  CHECK(s.isNull() == false);
  CHECK(s.size() == 5);
}

TEST_CASE("custom_string") {
  custom_string orig("bravo");
  SizedRamString s = adaptString(orig);

  CHECK(stringCompare(s, "alpha", 5) > 0);
  CHECK(stringCompare(s, "bravo", 5) == 0);
  CHECK(stringCompare(s, "charlie", 7) < 0);

  CHECK(s.isNull() == false);
  CHECK(s.size() == 5);
}

TEST_CASE("IsString<T>") {
  SECTION("std::string") {
    CHECK(IsString<std::string>::value == true);
  }

  SECTION("basic_string<wchar_t>") {
    CHECK(IsString<std::basic_string<wchar_t> >::value == false);
  }

  SECTION("custom_string") {
    CHECK(IsString<custom_string>::value == true);
  }

  SECTION("const __FlashStringHelper*") {
    CHECK(IsString<const __FlashStringHelper*>::value == true);
  }

  SECTION("const char*") {
    CHECK(IsString<const char*>::value == true);
  }

  SECTION("const char[]") {
    CHECK(IsString<const char[8]>::value == true);
  }
}

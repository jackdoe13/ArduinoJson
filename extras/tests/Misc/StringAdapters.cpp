// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#define ARDUINOJSON_ENABLE_PROGMEM 1
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#include "custom_string.hpp"
#include "progmem_emulation.hpp"
#include "weird_strcmp.hpp"

#include <ArduinoJson/Strings/StringAdapters.hpp>

#include <catch.hpp>

using namespace ARDUINOJSON_NAMESPACE;

TEST_CASE("const char*") {
  SECTION("null") {
    ZeroTerminatedRamStringAdapter adapter =
        adaptString(static_cast<const char*>(0));

    CHECK(adapter.size() == 0);
  }

  SECTION("non-null") {
    ZeroTerminatedRamStringAdapter adapter = adaptString("bravo");

    CHECK(adapter.compare("alpha") > 0);
    CHECK(adapter.compare("bravo") == 0);
    CHECK(adapter.compare("charlie") < 0);

    CHECK(adapter.size() == 5);
  }
}

TEST_CASE("const char* + size") {
  SECTION("null") {
    SizedRamStringAdapter adapter =
        adaptString(static_cast<const char*>(0), 10);

    CHECK(adapter.isNull() == true);
    CHECK(adapter.size() == 10);
  }

  SECTION("non-null") {
    SizedRamStringAdapter adapter = adaptString("bravo", 5);

    CHECK(adapter.compare("alpha") > 0);
    CHECK(adapter.compare("bravo") == 0);
    CHECK(adapter.compare("charlie") < 0);

    CHECK(adapter.isNull() == false);
    CHECK(adapter.size() == 5);
  }
}

TEST_CASE("const __FlashStringHelper*") {
  SECTION("null") {
    FlashStringAdapter adapter =
        adaptString(static_cast<const __FlashStringHelper*>(0));

    CHECK(adapter.isNull() == true);
    CHECK(adapter.size() == 0);
  }

  SECTION("non-null") {
    FlashStringAdapter adapter = adaptString(F("bravo"));

    CHECK(adapter.compare("alpha") > 0);
    CHECK(adapter.compare("bravo") == 0);
    CHECK(adapter.compare("charlie") < 0);

    CHECK(adapter.isNull() == false);
    CHECK(adapter.size() == 5);
  }
}

TEST_CASE("std::string") {
  std::string str("bravo");
  SizedRamStringAdapter adapter = adaptString(str);

  CHECK(adapter.compare("alpha") > 0);
  CHECK(adapter.compare("bravo") == 0);
  CHECK(adapter.compare("charlie") < 0);

  CHECK(adapter.isNull() == false);
  CHECK(adapter.size() == 5);
}

TEST_CASE("Arduino String") {
  ::String str("bravo");
  SizedRamStringAdapter adapter = adaptString(str);

  CHECK(adapter.compare("alpha") > 0);
  CHECK(adapter.compare("bravo") == 0);
  CHECK(adapter.compare("charlie") < 0);

  CHECK(adapter.isNull() == false);
  CHECK(adapter.size() == 5);
}

TEST_CASE("custom_string") {
  custom_string str("bravo");
  SizedRamStringAdapter adapter = adaptString(str);

  CHECK(adapter.compare("alpha") > 0);
  CHECK(adapter.compare("bravo") == 0);
  CHECK(adapter.compare("charlie") < 0);

  CHECK(adapter.isNull() == false);
  CHECK(adapter.size() == 5);
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

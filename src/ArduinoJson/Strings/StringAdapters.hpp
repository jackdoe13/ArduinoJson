// ArduinoJson - https://arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License

#pragma once

#include <ArduinoJson/Strings/Adapters/JsonString.hpp>
#include <ArduinoJson/Strings/Adapters/RamString.hpp>

#if ARDUINOJSON_ENABLE_STD_STRING
#  include <ArduinoJson/Strings/Adapters/StdString.hpp>
#endif

#if ARDUINOJSON_ENABLE_STRING_VIEW
#  include <ArduinoJson/Strings/Adapters/StringView.hpp>
#endif

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
#  include <ArduinoJson/Strings/Adapters/ArduinoString.hpp>
#endif

#if ARDUINOJSON_ENABLE_PROGMEM
#  include <ArduinoJson/Strings/Adapters/FlashString.hpp>
#endif

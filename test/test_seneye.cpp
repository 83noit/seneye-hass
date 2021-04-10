/*
Copyright (c) 2021, 83noit <32198131+83noit@users.noreply.github.com>
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#include <memory>

#include "catch_amalgamated.hpp"
#include "seneye.h"

class SeneyeMockDevice : public SeneyeInterface {
 public:
  SeneyeMockDevice();
  bool Write(const char*);
  bool Read(char*);

  char buffer[65];
  bool is_successful;

 private:
  SeneyeMockDevice(const SeneyeMockDevice&) = delete;
  SeneyeMockDevice& operator=(SeneyeMockDevice&) = delete;
};

SeneyeMockDevice::SeneyeMockDevice() : SeneyeInterface(), is_successful{true} {}

bool SeneyeMockDevice::Write(const char* data) {
  memcpy(buffer, (const char*)data, 65);
  return is_successful;
}

bool SeneyeMockDevice::Read(char* data) {
  memcpy((char*)data, buffer, 65);
  return is_successful;
}

constexpr char LIGHT_READING[65]{
    0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0C, 0xA0, 0x5F, 0x00, 0xA2, 0x07, 0x00, 0x00,
    0xD5, 0x0A, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x5D, 0x05, 0x00,
    0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

constexpr char LIGHT_READING2[65]{
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x9F, 0x02, 0x00,
    0x00, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

constexpr char SENSOR_READING[65]{
    0x00, 0x01, 0x0C, 0x39, 0x70, 0x60, 0x15, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xA2, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x5C,
    0x60, 0x00, 0xD7, 0x06, 0x00, 0x00, 0x58, 0x0A, 0x00, 0x00, 0x27,
    0x00, 0x00, 0x00, 0x76, 0x05, 0x00, 0x00, 0x44, 0x00};

constexpr char SENSOR_READING2[65]{
    0x00, 0x01, 0xAD, 0xB3, 0x70, 0x60, 0x05, 0x00, 0x00, 0x00, 0x29,
    0x03, 0x07, 0x00, 0xA8, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13,
    0x00, 0x00, 0x00, 0xA4, 0x02, 0x00, 0x00, 0x4B, 0x00};

constexpr char SENSOR_READING3[65]{
    0x00, 0x01, 0x0B, 0xCA, 0x70, 0x60, 0x05, 0x00, 0x00, 0x00, 0x2A,
    0x03, 0x07, 0x00, 0xAE, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

TEST_CASE("Seneye is successfully inilialized", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  Seneye device(dynamic_cast<SeneyeInterface*>(mock));
  REQUIRE(device.device_type() == "Unknown");
  REQUIRE(device.device_version() == "0.0.0");
  REQUIRE(device.serial_number() == "Unknown");
  REQUIRE_FALSE(device.is_kelvin());
  REQUIRE(device.kelvin() == 0);
  REQUIRE(device.x() == 0);
  REQUIRE(device.y() == 0);
  REQUIRE(device.par() == 0);
  REQUIRE(device.lux() == 0);
  REQUIRE(device.pur() == 0);
  REQUIRE(device.reading_timestamp() == 0);
  REQUIRE_FALSE(device.is_in_water());
  REQUIRE_FALSE(device.has_slide());
  REQUIRE_FALSE(device.has_expired_slide());
  REQUIRE(device.ph() == 0);
  REQUIRE(device.nh3() == 0);
  REQUIRE(device.temperature() == 0);
  REQUIRE(mock->buffer[1] == 'H');
  REQUIRE(mock->buffer[2] == 'E');
  REQUIRE(mock->buffer[3] == 'L');
  REQUIRE(mock->buffer[4] == 'L');
  REQUIRE(mock->buffer[5] == 'O');
  REQUIRE(mock->buffer[6] == 'S');
  REQUIRE(mock->buffer[7] == 'U');
  REQUIRE(mock->buffer[8] == 'D');
  REQUIRE(mock->buffer[9] == 0);
}

TEST_CASE("Seneye is not successfully inilialized", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  mock->is_successful = false;
  REQUIRE_THROWS_AS(Seneye(dynamic_cast<SeneyeInterface*>(mock)),
                    InitializationException);
}

TEST_CASE("Read() returns true when successul", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  Seneye device(dynamic_cast<SeneyeInterface*>(mock));
  memcpy(mock->buffer, LIGHT_READING, 65);
  REQUIRE(device.Read() == Seneye::LIGHT);
}

TEST_CASE("Read() returns false when unsuccessul", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  Seneye device(dynamic_cast<SeneyeInterface*>(mock));
  memcpy(mock->buffer, LIGHT_READING, 65);
  mock->is_successful = false;
  REQUIRE(device.Read() == Seneye::ERROR);
}

TEST_CASE("Seneye can read light reading", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  Seneye device(dynamic_cast<SeneyeInterface*>(mock));
  memcpy(mock->buffer, LIGHT_READING, 65);
  REQUIRE_FALSE(device.is_kelvin());
  REQUIRE(device.kelvin() == 0);
  REQUIRE(device.x() == 0);
  REQUIRE(device.y() == 0);
  REQUIRE(device.par() == 0);
  REQUIRE(device.lux() == 0);
  REQUIRE(device.pur() == 0);
  REQUIRE(device.Read() == Seneye::LIGHT);
  REQUIRE_FALSE(device.Read() == Seneye::SENSOR);
  REQUIRE(device.is_kelvin());
  REQUIRE(device.kelvin() == 6266892);
  REQUIRE(device.x() == 1954);
  REQUIRE(device.y() == 2773);
  REQUIRE(device.par() == 38);
  REQUIRE(device.lux() == 1373);
  REQUIRE(device.pur() == 67);
}

TEST_CASE("Seneye can read light reading (2)", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  Seneye device(dynamic_cast<SeneyeInterface*>(mock));
  memcpy(mock->buffer, LIGHT_READING2, 65);
  REQUIRE(device.Read() == Seneye::LIGHT);
  REQUIRE_FALSE(device.is_kelvin());
  REQUIRE(device.kelvin() == 0);
  REQUIRE(device.x() == 0);
  REQUIRE(device.y() == 0);
  REQUIRE(device.par() == 19);
  REQUIRE(device.lux() == 671);
  REQUIRE(device.pur() == 74);
}

TEST_CASE("Seneye can read sensor reading", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  Seneye device(dynamic_cast<SeneyeInterface*>(mock));
  memcpy(mock->buffer, SENSOR_READING, 65);
  REQUIRE_FALSE(device.is_kelvin());
  REQUIRE(device.kelvin() == 0);
  REQUIRE(device.x() == 0);
  REQUIRE(device.y() == 0);
  REQUIRE(device.par() == 0);
  REQUIRE(device.lux() == 0);
  REQUIRE(device.pur() == 0);
  REQUIRE(device.reading_timestamp() == 0);
  REQUIRE_FALSE(device.is_in_water());
  REQUIRE_FALSE(device.has_slide());
  REQUIRE_FALSE(device.has_expired_slide());
  REQUIRE(device.ph() == 0);
  REQUIRE(device.nh3() == 0);
  REQUIRE(device.temperature() == 0);
  REQUIRE(device.Read() == Seneye::SENSOR);
  REQUIRE(device.is_kelvin());
  REQUIRE(device.kelvin() == 6315035);
  REQUIRE(device.x() == 1751);
  REQUIRE(device.y() == 2648);
  REQUIRE(device.par() == 39);
  REQUIRE(device.lux() == 1398);
  REQUIRE(device.pur() == 68);
  REQUIRE(device.reading_timestamp() == 1617967372);
  REQUIRE(device.is_in_water());
  REQUIRE(device.has_slide());
  REQUIRE(device.has_expired_slide());
  REQUIRE(device.ph() == 0);
  REQUIRE(device.nh3() == 0);
  REQUIRE(device.temperature() == 25250);
}

TEST_CASE("Seneye can read sensor reading (2)", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  Seneye device(dynamic_cast<SeneyeInterface*>(mock));
  memcpy(mock->buffer, SENSOR_READING2, 65);
  REQUIRE(device.Read() == Seneye::SENSOR);
  REQUIRE_FALSE(device.is_kelvin());
  REQUIRE(device.kelvin() == 0);
  REQUIRE(device.x() == 0);
  REQUIRE(device.y() == 0);
  REQUIRE(device.par() == 19);
  REQUIRE(device.lux() == 676);
  REQUIRE(device.pur() == 75);
  REQUIRE(device.reading_timestamp() == 1617998765);
  REQUIRE(device.is_in_water());
  REQUIRE(device.has_slide());
  REQUIRE_FALSE(device.has_expired_slide());
  REQUIRE(device.ph() == 809);
  REQUIRE(device.nh3() == 7);
  REQUIRE(device.temperature() == 25000);
}

TEST_CASE("Seneye can read sensor reading (3)", "[Seneye]") {
  SeneyeMockDevice* mock = new SeneyeMockDevice();
  Seneye device(dynamic_cast<SeneyeInterface*>(mock));
  memcpy(mock->buffer, SENSOR_READING3, 65);
  REQUIRE(device.Read() == Seneye::SENSOR);
  REQUIRE_FALSE(device.is_kelvin());
  REQUIRE(device.kelvin() == 0);
  REQUIRE(device.x() == 0);
  REQUIRE(device.y() == 0);
  REQUIRE(device.par() == 0);
  REQUIRE(device.lux() == 0);
  REQUIRE(device.pur() == 0);
  REQUIRE(device.reading_timestamp() == 1618004491);
  REQUIRE(device.is_in_water());
  REQUIRE(device.has_slide());
  REQUIRE_FALSE(device.has_expired_slide());
  REQUIRE(device.ph() == 810);
  REQUIRE(device.nh3() == 7);
  REQUIRE(device.temperature() == 24750);
}

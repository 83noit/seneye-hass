/*
Copyright (c) 2021, 83noit <32198131+83noit@users.noreply.github.com>
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#include <cstring>

#include "sud.h"

SeneyeInterface::SeneyeInterface() {}

SeneyeInterface::~SeneyeInterface() {}

Seneye::Seneye() : Seneye(dynamic_cast<SeneyeInterface*>(new SeneyeDevice())) {}

Seneye::Seneye(SeneyeInterface* device)
    : device_{device},
      device_type_{"Unknown"},
      device_version_{"0.0.0"},
      serial_number_{"Unknown"},
      is_kelvin_{false},
      kelvin_{0},
      x_{0},
      y_{0},
      par_{0},
      lux_{0},
      pur_{0},
      reading_timestamp_{0},
      is_in_water_{false},
      has_slide_{false},
      has_expired_slide_{false},
      ph_{0},
      nh3_{0},
      temperature_{0} {
  if (!EnterInteractiveMode())
    throw InitializationException("Unable to perform handshake.");
}

std::string Seneye::device_type() { return device_type_; }

std::string Seneye::device_version() { return device_version_; }

std::string Seneye::serial_number() { return serial_number_; }

bool Seneye::is_kelvin() { return is_kelvin_; }

int Seneye::kelvin() { return kelvin_; }

int Seneye::x() { return x_; }

int Seneye::y() { return y_; }

unsigned int Seneye::par() { return par_; }

unsigned int Seneye::lux() { return lux_; }

unsigned int Seneye::pur() { return pur_; }

unsigned int Seneye::reading_timestamp() { return reading_timestamp_; }

bool Seneye::is_in_water() { return is_in_water_; }

bool Seneye::has_slide() { return has_slide_; }

bool Seneye::has_expired_slide() { return has_expired_slide_; }

unsigned int Seneye::ph() { return ph_; }

unsigned int Seneye::nh3() { return nh3_; }

int Seneye::temperature() { return temperature_; }

const char* Seneye::buffer() { return (const char*)&buffer_; }

bool Seneye::EnterInteractiveMode() {
  memset(&buffer_, 0x00, 65);
  strcpy(&buffer_[1], "HELLOSUD");
  return device_->Write(buffer_);
}

bool Seneye::LeaveInteractiveMode() {
  memset(&buffer_, 0x00, 65);
  strcpy(&buffer_[1], "BYESUD");
  return device_->Write(buffer_);
}

Seneye::~Seneye() {
  LeaveInteractiveMode();
  delete device_;
}

Seneye::ReadingType Seneye::Read() {
  if (!device_->Read(buffer_)) return ReadingType::ERROR;
  if (LightReading()) return ReadingType::LIGHT;
  if (SensorReading()) return ReadingType::SENSOR;
  return ReadingType::ERROR;
}

bool Seneye::LightReading() {
  /* See https://github.com/seneye/SUDDriver/blob/master/Cpp/sud_data.h */
  if (buffer_[0] != 0x00 || buffer_[1] != 0x02) return false;
  /*  Little Endian data. */
  /* uint32_t: Valid Kelvin measure is taken. */
  is_kelvin_ = int(buffer_[2] | buffer_[3] << 8 | buffer_[4] << 16 |
                   buffer_[5] << 24) != 0;
  LightReadingPart(false);
  return true;
}

bool Seneye::SensorReading() {
  /* See https://github.com/seneye/SUDDriver/blob/master/Cpp/sud_data.h */
  if (buffer_[0] != 0x00 || buffer_[1] != 0x01) return false;
  /*  Little Endian data. */
  /* uint32_t: Unix Timestamp. */
  reading_timestamp_ = (unsigned int)(buffer_[2] | buffer_[3] << 8 |
                                      buffer_[4] << 16 | buffer_[5] << 24);
  /* 2 unused bits. */
  /* 1 bit: In or out of water. */
  is_in_water_ = (buffer_[6] & (1 << 2)) != 0;
  /* 1 bit: Not fitted slide. */
  has_slide_ = (buffer_[6] & (1 << 3)) == 0;
  /* 1 bit: Has the slide expired? */
  has_expired_slide_ = (buffer_[6] & (1 << 4)) != 0;
  /* 2 bits: StateT. Unknown use. */
  /* 2 bits: StatePh. Unknown use. */
  /* 2 bits: StateNH3. Unknown use. */
  /* 1 bit: Error. Unknown use. */
  /* 1 bit: Valid Kelvin measure is taken. */
  is_kelvin_ = (buffer_[7] & (1 << 4)) != 0;
  /* uint16_t: pH level (x100). */
  ph_ = (unsigned int)(buffer_[10] | buffer_[11] << 8);
  /* uint16_t: Ammonia level (x1000). */
  nh3_ = (unsigned int)(buffer_[12] | buffer_[13] << 8);
  /* int32_t: Temperature (x1000).  */
  temperature_ = int(buffer_[14] | buffer_[15] << 8 | buffer_[16] << 16 |
                     buffer_[17] << 24);
  /* 16 unused bytes. */
  /* Followed by a light reading starting from the 8 unused bytes. */
  LightReadingPart(true);
  return true;
}

void Seneye::LightReadingPart(bool is_sensor_reading) {
  /* See https://github.com/seneye/SUDDriver/blob/master/Cpp/sud_data.h */
  /* A light reading can occur by itself (after 6 bytes of payload) or as
   * part of a sensor reading (after 34 bytes).
   * It starts by 8 unused bytes. */
  int i{(is_sensor_reading ? 34 : 6) + 8};
  /*  Little Endian data. */
  /* int32_t: Light colour temperature in the Kelvin scale (x1000). */
  kelvin_ = int(buffer_[i] | buffer_[i + 1] << 8 | buffer_[i + 2] << 16 |
                buffer_[i + 3] << 24);
  /* int32_t: X coordinate on the CIE colourspace. */
  x_ = int(buffer_[i + 4] | buffer_[i + 5] << 8 | buffer_[i + 6] << 16 |
           buffer_[i + 7] << 24);
  /* int32_t: Y coordinate on the CIE colourspace. */
  y_ = int(buffer_[i + 8] | buffer_[i + 9] << 8 | buffer_[i + 10] << 16 |
           buffer_[i + 11] << 24);
  /* uint32_t: PAR light level. */
  par_ = (unsigned int)(buffer_[i + 12] | buffer_[i + 13] << 8 |
                        buffer_[i + 14] << 16 | buffer_[i + 15] << 24);
  /* uint32_t: Lux light level. */
  lux_ = (unsigned int)(buffer_[i + 16] | buffer_[i + 17] << 8 |
                        buffer_[i + 18] << 16 | buffer_[i + 19] << 24);
  /* uchar : PUR value in percentage. */
  pur_ = (unsigned int)(buffer_[i + 20]);
}

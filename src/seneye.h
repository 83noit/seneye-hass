/*
Copyright (c) 2021, 83noit <32198131+83noit@users.noreply.github.com>
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#ifndef SRC_SENEYE_H_
#define SRC_SENEYE_H_

#include <memory>
#include <stdexcept>
#include <string>

class InitializationException : public std::runtime_error {
 public:
  InitializationException()
      : InitializationException("Failed to initialize Seneye device.") {}
  InitializationException(const char* what_arg) : runtime_error(what_arg) {}
};

class SeneyeInterface {
 public:
  virtual bool Write(const unsigned char*) = 0;
  virtual bool Read(unsigned char*) = 0;
  virtual ~SeneyeInterface();

 protected:
  SeneyeInterface();
};

class Seneye {
 public:
  Seneye();
  Seneye(SeneyeInterface*);
  ~Seneye();
  std::string device_type();
  std::string device_version();
  std::string serial_number();
  const unsigned char* buffer();
  enum ReadingType { ERROR = 0, LIGHT, SENSOR };
  ReadingType Read();

  bool is_kelvin();
  int kelvin();
  int x();
  int y();
  unsigned int par();
  unsigned int lux();
  unsigned int pur();

  unsigned int reading_timestamp();
  bool is_in_water();
  bool has_slide();
  bool has_expired_slide();
  unsigned int ph();
  unsigned int nh3();
  int temperature();

 private:
  Seneye(const Seneye&) = delete;
  Seneye& operator=(Seneye&) = delete;
  bool EnterInteractiveMode();
  bool LeaveInteractiveMode();
  bool SensorReading();
  bool LightReading();
  void LightReadingPart(bool is_sensor_reading);

  unsigned char buffer_[65];
  SeneyeInterface* device_;
  std::string device_type_;
  std::string device_version_;
  std::string serial_number_;

  bool is_kelvin_;  // Valid Kelvin measure is taken.
  int kelvin_;      // Light colour temperature in the Kelvin scale (x1000).
  /* See
   * https://answers.seneye.com/en/Seneye_Products/seneye_USB_device/seneye_reef_light_meter_functions/no_kelvin_on_light_readings/
   */
  /* Limited to colors that are near the Kelvin line. Check with is_kelvin(). */
  int x_;             // X coordinate on the CIE colourspace.
  int y_;             // Y coordinate on the CIE colourspace.
  unsigned int par_;  // PAR light level.
  unsigned int lux_;  // Lux light level.
  unsigned int pur_;  // PUR value in percentage.

  unsigned int reading_timestamp_;  // Unix Timestamp.
  bool is_in_water_;
  bool has_slide_;
  bool has_expired_slide_;
  unsigned int ph_;   // pH level (x100).
  unsigned int nh3_;  // Ammonia level (x1000).
  int temperature_;   // Temperature (x1000). TODO: Celcius or Farenheit?
};

#endif  // SRC_SENEYE_H_

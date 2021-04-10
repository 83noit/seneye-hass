/*
Copyright (c) 2021, 83noit <32198131+83noit@users.noreply.github.com>
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#include <chrono>
#include <cstring>  // For memset
#include <thread>

#include "log.h"
#include "mqtt_client.h"
#include "sud.h"

int main() {
  std::clog.rdbuf(new Log("seneye", LOG_LOCAL0));
  MqttClient mqtt("seneye", "aquarium/seneye", "192.168.86.60", 1883);
  char payload[200];
  try {
    Seneye device;
    while (1) {
      if (mqtt.loop()) {
        mqtt.reconnect();
      }
      switch (device.Read()) {
        case Seneye::SENSOR:
          memset(&payload, 0x00, 65);
          snprintf(payload, sizeof(payload),
                   "{\"timestamp\": %d, "
                   "\"ph\": %d, "
                   "\"nh3\": %d, "
                   "\"temperature\": %d, "
                   "\"is_in_water\": %d, "
                   "\"has_slide\": %d, "
                   "\"has_expired_slide\": %d, "
                   "\"is_kelvin\": %d, "
                   "\"kelvin\": %d, "
                   "\"par\": %d, "
                   "\"lux\": %d, "
                   "\"pur\": %d}",
                   device.reading_timestamp(), device.ph(), device.nh3(),
                   device.temperature(), device.is_in_water(),
                   device.has_slide(), device.has_expired_slide(),
                   device.is_kelvin(), device.kelvin(), device.par(),
                   device.lux(), device.pur());
          mqtt.send_message(payload, "aquarium/seneye/sensor");
          std::clog << kLogInfo << payload << std::endl;
          break;
        case Seneye::LIGHT:
          memset(&payload, 0x00, 65);
          snprintf(payload, sizeof(payload),
                   "{\"is_kelvin\": %d, "
                   "\"kelvin\": %d, "
                   "\"par\": %d, "
                   "\"lux\": %d, "
                   "\"pur\": %d}",
                   device.is_kelvin(), device.kelvin(), device.par(),
                   device.lux(), device.pur());
          mqtt.send_message(payload, "aquarium/seneye/light");
          std::clog << kLogInfo << payload << std::endl;
          break;
        default:
          break;
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  } catch (const std::exception &e) {
    std::clog << kLogCrit << e.what() << std::endl;
    return -1;
  }
  return 0;
}

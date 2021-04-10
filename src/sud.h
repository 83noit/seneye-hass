/*
Copyright (c) 2021, 83noit <32198131+83noit@users.noreply.github.com>
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#ifndef SRC_SENEYE_DEVICE_H_
#define SRC_SENEYE_DEVICE_H_

#include <hidapi/hidapi.h>

#include "seneye.h"

class SeneyeDevice : public SeneyeInterface {
  /* Encapsulates a Seneye USB Device and its capabilities. */
  // https://github.com/seneye/SUDDriver
 public:
  static constexpr int VENDOR_ID = 9463;
  static constexpr int PRODUCT_ID = 8708;

  SeneyeDevice();
  ~SeneyeDevice();
  bool Write(const char *);
  bool Read(char *);

 private:
  SeneyeDevice(const SeneyeDevice &) = delete;
  SeneyeDevice &operator=(SeneyeDevice &) = delete;

  hid_device *handle_;
  struct hid_device_info *devs_;
};

#endif  // SRC_SENEYE_DEVICE_H_

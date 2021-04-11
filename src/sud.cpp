/*
Copyright (c) 2021, 83noit <32198131+83noit@users.noreply.github.com>
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#include "sud.h"

SeneyeDevice::SeneyeDevice()
    : SeneyeInterface{}, handle_{nullptr}, devs_{nullptr} {
  if (hid_init()) throw InitializationException();
  devs_ = hid_enumerate(SeneyeDevice::VENDOR_ID, SeneyeDevice::PRODUCT_ID);
  if (devs_ == nullptr) throw InitializationException("No available device.");
  handle_ = hid_open_path(devs_->path);
  if (!handle_) throw InitializationException("Unable to open device.");
  hid_set_nonblocking(handle_, 1);
}

SeneyeDevice::~SeneyeDevice() {
  hid_close(handle_);
  free(devs_);
}

bool SeneyeDevice::Write(const unsigned char* buffer) {
  return hid_write(handle_, buffer, 65) >= 0;
}

bool SeneyeDevice::Read(unsigned char* buffer) {
  return hid_read(handle_, buffer, 64) == 64;
}

/**
 * @file gps_device.h
 * @brief
 * @author boo
 * @copyright
 */

#pragma once

#include "io/device.h"

class GPSDevice : public EAR::IO::Device {
public:
  GPSDevice(const std::string &name, const std::string &model, const std::string &version);
  virtual ~GPSDevice();
  virtual int32_t initialize(void) override;
  virtual int32_t shutdown(void) override;
  virtual int32_t receive(void *buf, const uint16_t size) override;
  virtual int32_t transmit(const void *buf, const uint16_t size) override;
  virtual int32_t configure(void *target, const int32_t op) override;
};

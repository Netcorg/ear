#pragma once

#include "io/controller.h"

class SerialController : public EAR::IO::Controller {
 public:
  explicit SerialController(const std::string &name);  
  virtual ~SerialController();
  virtual int32_t open(void *param) override;
  virtual int32_t close(void) override;
  virtual int32_t read(void *buf, const uint16_t size) override;
  virtual int32_t write(const void *buf, const uint16_t size) override;
};

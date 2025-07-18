#include "gps_device.h"

GPSDevice::GPSDevice(const std::string &name, const std::string &model, const std::string &version)
    : EAR::IO::Device(name, model, version)
{
}

GPSDevice::~GPSDevice() {

}

int32_t GPSDevice::initialize(void) {
  if (nullptr == m_controller) {
    return -1;
  }
  
  return m_controller->open(nullptr);
}

int32_t GPSDevice::shutdown(void) {
  if (nullptr == m_controller) {
    return -1;
  }
  
  return m_controller->close();
}

int32_t GPSDevice::receive(void *buf, const uint16_t size) {
  if (nullptr == m_controller) {
    return -1;
  }

  // you may deserialize if you need or perform conversion, scaling,
  // parsing, range/limit check right here  
  return m_controller->read(buf, size);
}

int32_t GPSDevice::transmit(const void *buf, const uint16_t size) {
  if (nullptr == m_controller) {
    return -1;
  }
    
  // you may serialize if you need
  return m_controller->write(buf, size);
}

int32_t GPSDevice::configure(void *target, const int32_t op) {
  return -1;
}

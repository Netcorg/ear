#include "location_service.h"
#include "spdlog/spdlog.h"

LocationService::LocationService(const std::string &name)
  : EAR::Schedule::PeriodicTask(name)
{
}

LocationService::~LocationService()
{
}

void LocationService::setDevice(EAR::IO::Device *dev) {
  m_dev = dev;
  return;
}

bool LocationService::initialize(void) {
  spdlog::info("Location Service task {} initialized", getName());
  return m_endpoint.initialize("127.0.0.1", 5000);
}

void LocationService::cycle(void) {
  int32_t size = 8U;
  uint8_t data[8];
	
  if (nullptr != m_dev) {
    if (0 < m_dev->receive(data, size)) {
      spdlog::info("{} received data from device {}", getName(), m_dev->toString());
    }
    else {
      spdlog::warn("Location Service task {} read failed", getName());
    }
  }

  if (m_endpoint.transmit(data, size)) {
    spdlog::info("location service transmits data to dcu service");
  }
  else {
    spdlog::error("location service could not transmit data to dcu service");
  }
    
  return;
}

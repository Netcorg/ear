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
  
  return true;
}

void LocationService::cycle(void) {
  const uint16_t size = 8U;
  uint8_t data[size];
	
  if (nullptr != m_dev) {
    if (0 < m_dev->receive(data, size)) {
      spdlog::info("{} received data from device {}", getName(), m_dev->toString());
    }
    else {
      spdlog::warn("Location Service task {} read failed", getName());
    }
  }
    
  return;
}

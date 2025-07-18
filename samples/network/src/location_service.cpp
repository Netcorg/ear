#include "location_service.h"
#include "spdlog/spdlog.h"

LocationService::LocationService(const std::string &name)
  : EAR::Schedule::PeriodicTask(name)
{
}

LocationService::~LocationService() {
  m_endpoint.shutdown();
}

void LocationService::setDevice(EAR::IO::Device *dev) {
  m_dev = dev;
  return;
}

void LocationService::setEndpointConfiguration(const EAR::Communication::Configuration &ep_config) {
  m_ep_config = ep_config;
  return;
}

bool LocationService::initialize(void) {
  if (!m_endpoint.initialize(m_ep_config)) {
    spdlog::error("could not initialize endpoint of task {}", getName());
    return false;
  }

  spdlog::info("LocationService task {} initialized", getName());
  return true;
}

void LocationService::cycle(void) {
  uint8_t data[8];
	
  if (nullptr != m_dev) {
    if (0 < m_dev->receive(data, 8)) {
      spdlog::info("{} received data from device {}", getName(), m_dev->toString());

      if (EAR::Communication::COMM_OPENED == m_endpoint.getState()) {
	size_t size = 8;
		
	if (0 < m_endpoint.send(data, size)) {
	  spdlog::info("send data to DCU [{}]", getName());
	}
	else {
	  spdlog::error("could not send data to DCU [{}]", getName());
	}
      }
    }
    else {
      spdlog::warn("LocationService task {} read failed", getName());
    }
  }
    
  return;
}

#include "dcu_service.h"
#include "position.h"
#include "spdlog/spdlog.h"

DCUService::DCUService(const std::string &name)
  : EAR::Schedule::PeriodicTask(name)
{
}

DCUService::~DCUService() {
  m_endpoint.shutdown();
}

void DCUService::setEndpointConfiguration(const EAR::Communication::Configuration &ep_config) {
  m_ep_config = ep_config;
  return;
}

bool DCUService::initialize(void) {
  if (!m_endpoint.initialize(m_ep_config)) {
    spdlog::error("could not initialize endpoint of task {}", getName());
    return false;
  }

  spdlog::debug("DCUService task {} initialized", getName());
  return true;
}

void DCUService::cycle(void) {
  Position pos;
  size_t size = 8;

  if (EAR::Communication::COMM_OPENED == m_endpoint.getState()) {
    while (0 < m_endpoint.receive(&pos, size)) {
      spdlog::info("DCUService get data, lon {}, lat {}",
		   pos.longitude, pos.latitude);
    }
  }
  
  return;
}

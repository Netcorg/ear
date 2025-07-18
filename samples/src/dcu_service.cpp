#include "dcu_service.h"
#include "spdlog/spdlog.h"

DCUService::DCUService(const std::string &name) :
  EAR::Schedule::PeriodicTask(name)
{
}

DCUService::~DCUService() {
}

bool DCUService::initialize(void) {
  spdlog::debug("DCUService task {} initialized", getName());
  return m_endpoint.initialize(5000, true);
}

void DCUService::cycle(void) {
  int32_t size = 8U;
  uint8_t data[8];
	 
  if (m_endpoint.receive(data, size)) {
    spdlog::info("dcu service receives data from location service");
  }
  else {
    spdlog::error("dcu service could not receive data from location service");
  }
  
  return;
}

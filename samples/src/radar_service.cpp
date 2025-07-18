#include "radar_service.h"
#include "spdlog/spdlog.h"

RadarService::RadarService(const std::string &name) :
  EAR::Schedule::OneShotTask(name)
{
}

RadarService::~RadarService() {
}

bool RadarService::initialize(void) {
  spdlog::debug("RadarService task {} initialized", getName());
  return true;
}

void RadarService::cycle(void) {
  while (m_is_running) {
    spdlog::info("rendering radar screen...");
    std::this_thread::sleep_for(std::chrono::microseconds(200000));
  }
  
  return;
}

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
  return true;
}

void DCUService::cycle(void) {
  spdlog::info("DCUService process called");
  return;
}

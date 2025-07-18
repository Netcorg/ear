#pragma once

#include "sched/periodic_task.h"
#include "comm/receiver.h"

class DCUService : public EAR::Schedule::PeriodicTask {
public:
  explicit DCUService(const std::string &name);
  virtual ~DCUService();
  virtual bool initialize(void) override;
  virtual void cycle(void) override;

private:
  EAR::Communication::Receiver m_endpoint {"dcu-ep"};
};

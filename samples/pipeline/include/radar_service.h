#pragma once

#include "sched/one_shot_task.h"

class RadarService : public EAR::Schedule::OneShotTask {
public:
  explicit RadarService(const std::string &name);
  virtual ~RadarService();
  virtual bool initialize(void) override;
  virtual void cycle(void) override;
};

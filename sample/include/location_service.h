#pragma once

#include "io/device.h"
#include "sched/periodic_task.h"
#include "comm/transmitter.h"

class LocationService : public EAR::Schedule::PeriodicTask {
public:
  explicit LocationService(const std::string &name);
  virtual ~LocationService();
  void setDevice(EAR::IO::Device *dev);
  virtual bool initialize() override;
  virtual void cycle() override;

private:
  EAR::IO::Device *m_dev = nullptr;
  EAR::Communication::Transmitter m_endpoint {"loc-serv-ep"};
};

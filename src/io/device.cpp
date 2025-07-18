#include <sstream>
#include "io/device.h"

EAR::IO::Device::Device(const std::string &name, const std::string &model, const std::string &version)
  : m_name(name), m_model(model), m_version(version)
{
}

EAR::IO::Device::~Device(void) {
}

std::string EAR::IO::Device::getName(void) const {
  return m_name;
}

std::string EAR::IO::Device::getModel(void) const {
  return m_model;
}

std::string EAR::IO::Device::getVersion(void) const {
  return m_version;
}

EAR::IO::State EAR::IO::Device::getState(void) const {
  return m_state;
}

void EAR::IO::Device::setController(EAR::IO::Controller *controller) {
  m_controller = controller;
  return;
}

std::string EAR::IO::Device::toString(void) const {
  std::stringstream ss;
  ss << m_name << " device [" << m_model << " - " << m_version << "]";
  
  return ss.str();
}

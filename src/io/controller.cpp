#include "io/controller.h"

EAR::IO::Controller::Controller(const std::string &name)
  : m_name(name)
{
}

EAR::IO::Controller::~Controller() {

}

std::string EAR::IO::Controller::getName(void) const {
  return m_name;
}

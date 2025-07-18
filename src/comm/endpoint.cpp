#include <vector>
#include <exception>
#include "comm/endpoint.h"

EAR::Communication::Endpoint::Endpoint(void) {
}

EAR::Communication::Endpoint::Endpoint(const std::string &name)
  : m_name(name)
{
}

EAR::Communication::Endpoint::~Endpoint() {
}

void EAR::Communication::Endpoint::setName(const std::string &name) {
  m_name = name;
  return;
}

const std::string &EAR::Communication::Endpoint::getName(void) const {
  return m_name;
}

EAR::Communication::State EAR::Communication::Endpoint::getState(void) const {
  return m_state;
}

bool EAR::Communication::Endpoint::isValidAddress(std::string addr) {
  size_t pos = 0;
  std::string delimiter = ".";
  std::string token;
  std::vector<int> fields;

  try {
    while ((pos = addr.find(delimiter)) != std::string::npos) {
      token = addr.substr(0, pos);
      fields.push_back(std::stoi(token));
      addr.erase(0, pos + delimiter.length());
    }

    fields.push_back(std::stoi(addr));

    // check IP v4
    if (4 != fields.size()) {
      return false;
    }

    for(auto &field : fields) {
      if (field > 255) {
	return false;
      }
    }
  } catch (std::exception &ex) {
    return false;
  }
    
  return true;
}

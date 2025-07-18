#include "comm/transmitter.h"
#include "spdlog/spdlog.h"

EAR::Communication::Transmitter::Transmitter(void) {
  // set default name
  m_name = "transmitter endpoint";
}

EAR::Communication::Transmitter::Transmitter(const std::string &name) {
  m_name = name;
}

EAR::Communication::Transmitter::~Transmitter() {
  if (nullptr != m_socket) {
    delete m_socket;
    m_socket = nullptr;
  }
}

void EAR::Communication::Transmitter::setName(const std::string &name) {
  m_name = name;
  return;
}

const std::string &EAR::Communication::Transmitter::getName(void) const {
  return m_name;
}

bool EAR::Communication::Transmitter::initialize(const std::string &remote_ip, const uint16_t remote_port) {
  if (remote_ip.empty() || 0U == remote_port) {
    spdlog::error("invalid ip {} and/or port {} configuration for {}", remote_ip, remote_port, m_name);
    return false;
  }

  if (nullptr != m_socket) {
    spdlog::error("could not open socket that was already opened for {}", m_name);
    return false;
  }
  
  try {
    m_socket = new asio::ip::udp::socket(m_context);
    m_remote_endpoint.address(asio::ip::make_address(remote_ip));
    m_remote_endpoint.port(remote_port);
    m_socket->open(asio::ip::udp::v4());
  }
  catch (asio::system_error &ex) {
    spdlog::error("could not initialize {}, error is {}", m_name, ex.what());
    return false;
  }
  
  return true;
}

bool EAR::Communication::Transmitter::shutdown(void) {
  if (nullptr == m_socket) {
    spdlog::error("could not close socket that is not opened yet for {}", m_name);
    return false;
  }

  m_socket->close();
  return true;
}

bool EAR::Communication::Transmitter::transmit(const uint8_t *buf, int32_t &size) {
  if (nullptr == m_socket) {
    spdlog::error("could not transmit data over socket that is not opened yet for {}", m_name);
    return false;
  }
  
  try {
    if (size != m_socket->send_to(asio::buffer(buf, size), m_remote_endpoint)) {
      spdlog::error("could not transmit all bytes to opposite side for {}", m_name);
      return false;
    }
  }
  catch (asio::system_error &ex) {
    spdlog::error("could not transmit data for {}, error is {}", m_name, ex.what());
    return false;
  }

  return true;
}

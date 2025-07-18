#include <array>
#include "comm/receiver.h"
#include "spdlog/spdlog.h"

EAR::Communication::Receiver::Receiver(void) {
  // set default name
  m_name = "receiver endpoint";
}

EAR::Communication::Receiver::Receiver(const std::string &name) {
  m_name = name;
}

EAR::Communication::Receiver::~Receiver() {
  if (nullptr != m_socket) {
    delete m_socket;
    m_socket = nullptr;
  }
}

void EAR::Communication::Receiver::setName(const std::string &name) {
  m_name = name;
  return;
}

const std::string &EAR::Communication::Receiver::getName(void) const {
  return m_name;
}


bool EAR::Communication::Receiver::initialize(const uint16_t local_port, bool is_nonblocking) {
  if (0U == local_port) {
    spdlog::error("invalid local port value {} for {}", local_port, m_name);
    return false;
  }

  if (nullptr != m_socket) {
    spdlog::error("could not open socket that was already opened for {}", m_name);
    return false;
  }
  
  try {
    asio::ip::udp::endpoint local_endpoint(asio::ip::udp::v4(), local_port);
    
    m_socket = new asio::ip::udp::socket(m_context);
    m_socket->open(asio::ip::udp::v4());
    m_socket->non_blocking(is_nonblocking);
    m_socket->bind(local_endpoint);
  }
  catch (asio::system_error &ex) {
    spdlog::error("could not initialize {}, error is {}", m_name, ex.what());
    return false;
  }
  
  return true;
}

bool EAR::Communication::Receiver::shutdown(void) {
  if (nullptr == m_socket) {
    spdlog::error("could not close socket that is not opened yet for {}", m_name);
    return false;
  }

  m_socket->close();
  return true;
}

bool EAR::Communication::Receiver::receive(uint8_t *buf, int32_t &size) {
  if (nullptr == m_socket) {
    spdlog::error("could not receive data over socket that is not opened yet for {}", m_name);
    return false;
  }

  if (nullptr == buf || 0U >= size || MAX_RECV_SIZE < size) {
    spdlog::error("could not receive data to invalid memory for {}", m_name);
    return false;
  }
  
  try {
    std::array<uint8_t, MAX_RECV_SIZE> temp_buf;
    
    size = m_socket->receive(asio::buffer(temp_buf));    
    memcpy(buf, temp_buf.data(), size);
  }
  catch (asio::system_error &ex) {
    // we do not care about the would_block error, because it is expected
    if (asio::error::would_block != ex.code()) {      
      spdlog::debug("could not receive data for {}, error is {}", m_name, ex.what());
    }
    
    return false;
  }
  
  return true;
}

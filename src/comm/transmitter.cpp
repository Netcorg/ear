#include <cstdlib>
#include <string>
#include <unistd.h>
#include "comm/transmitter.h"
#include "spdlog/spdlog.h"

EAR::Communication::Transmitter::Transmitter(void)
  : Endpoint()
{
}

EAR::Communication::Transmitter::Transmitter(const std::string &name)
  : Endpoint(name)
{
}

EAR::Communication::Transmitter::~Transmitter() {
}

bool EAR::Communication::Transmitter::initialize(const Configuration &config) {
  if (COMM_OPENED == m_state) {
    spdlog::error("socket for transmitter {} already opened", getName());
    return false;
  }

  memset(&m_remote_addr, 0, sizeof(m_remote_addr));

  if (config.ip.empty()) {
    m_remote_addr.sin_addr.s_addr = INADDR_ANY;
  }
  else {
    if (!isValidAddress(config.ip)) {
      spdlog::error("invalid IP format for transmitter {}", getName());
      return false;
    }

    m_remote_addr.sin_addr.s_addr = inet_addr(config.ip.c_str());
  }

  if (0 == config.port) {
    spdlog::error("invalid port number for transmitter {}", getName());
    return false;
  }

  m_remote_addr.sin_port = htons(config.port);
  m_remote_addr.sin_family = AF_INET;

  if (0 > (m_sock = socket(AF_INET, SOCK_DGRAM, 0))) {
    spdlog::error("could not create socket for transmitter {}", getName());
    return false;
  }

  m_state = COMM_OPENED;
  
  return true;
}

void EAR::Communication::Transmitter::shutdown(void) {
  struct sockaddr_in local_addr;
  socklen_t addr_len = sizeof(local_addr);
  char local_ip[16];

  if (0 == getsockname(m_sock, (struct sockaddr *) &local_addr, &addr_len)) {
    inet_ntop(AF_INET, &local_addr.sin_addr, local_ip, sizeof(local_ip));    
  }

  ::shutdown(m_sock, SHUT_WR);
  m_state = COMM_CLOSED;
    
  return;
}

int32_t EAR::Communication::Transmitter::send(const std::string &buf) {
  return send(buf.c_str(), buf.length());
}

int32_t EAR::Communication::Transmitter::send(const void *buf, size_t size) {
  if (COMM_OPENED != m_state) {
    spdlog::error("could not send data, connection closed for transmitter {}", getName());
    return ENOENT;
  }

  return sendto(m_sock, buf, size, 0,
		(struct sockaddr *) &m_remote_addr,
		sizeof(m_remote_addr));
}

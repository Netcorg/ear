/**
 * @file transmitter.h
 * @brief class that provides transmitting infrastructure for message transfer
 * @author boo
 */

#pragma once

#include <cstdint>
#include "asio.hpp"

namespace EAR {
  namespace Communication {
    /// transmitter endpoint class
    class Transmitter {	    
    public:
      /// default constructor
      Transmitter(void);      
      /// constructor
      /// @param [in] name - transmitter endpoint name
      Transmitter(const std::string &name);      
      /// destructor
      virtual ~Transmitter();
      /// function that sets transmitter endpoint name
      /// @param [in] name - endpoint name
      void setName(const std::string &name);
      /// function that gets transmitter endpoint name
      /// @return endpoint name
      const std::string &getName(void) const;
      /// function that initializes transmitter endpoint
      /// @param [in] remote_ip - ip address that is used to transmit data to destination
      /// @param [in] remote_port - port number that is used to transmit data to destination
      /// @return true if transmitter endpoint is initialized successfully, otherwise false     
      bool initialize(const std::string &remote_ip, const uint16_t remote_port);
      /// function that shutdowns transmitter endpoint
      /// @return true if transmitter endpoint is shut down successfully, otherwise false
      bool shutdown(void);    
      /// function that trasnmits buffer to receiver(s)
      /// @param [in] buf - buffer
      /// @param [in|out] size - buffer size
      /// @return true if transmission is done successfully, otherwise false
      bool transmit(const uint8_t *buf, int32_t &size);

    private:
      /// receiver endpoint name
      std::string m_name;
      /// io context for socket
      asio::io_context m_context;
      /// udp socket
      asio::ip::udp::socket *m_socket = nullptr;
      /// remote endpoint configuration
      asio::ip::udp::endpoint m_remote_endpoint;
    };
  }
}

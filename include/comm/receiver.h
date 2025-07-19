/**
 * @file receiver.h
 * @brief class that provides receiving infrastructure for message transfer
 * @author boo
 */

#pragma once

#include <cstdint>
#include "asio.hpp"

namespace EAR {
  namespace Communication {
    /// receiver endpoint class
    class Receiver {
    public:
      /// maximum size for receiving data
      static const uint16_t MAX_RECV_SIZE = 2048;

      /// default constructor
      Receiver(void);      
      /// constructor
      /// @param [in] name - receiver endpoint name
      Receiver(const std::string &name);
      /// destructor
      virtual ~Receiver();
      /// function that sets receiver endpoint name
      /// @param [in] name - endpoint name
      void setName(const std::string &name);
      /// function that gets receiver endpoint name
      /// @return endpoint name
      const std::string &getName(void) const;
      /// function that initializes receiver endpoint
      /// @param [in] local_port - local port number to be bind
      /// @param [in] is_nonblocking - nonblocking flag 
      /// @return true if receiver endpoint is initialized successfully, otherwise false
      bool initialize(const uint16_t local_port, bool is_nonblocking);
      /// function that shutdowns receiver endpoint
      /// @return true if receiver endpoint is shut down successfully, otherwise false
      bool shutdown(void);    
      /// function that receives buffer from transmitter(s)
      /// @param [in] buf - buffer
      /// @param [in|out] size - buffer size
      /// @return true if receive is done successfully, otherwise errno
      bool receive(uint8_t *buf, int32_t &size);

    private:
      /// receiver endpoint name
      std::string m_name;
      /// io context for socket
      asio::io_context m_context;
      /// udp socket
      asio::ip::udp::socket *m_socket = nullptr;
    };
  }
}

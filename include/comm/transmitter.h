/**
 * @file transmitter.h
 * @brief class that provides transmitting infrastructure for message transfer
 * Time-stamp: <2024-11-02 23:56:29 boo>
 */

#pragma once

#include <arpa/inet.h>
#include "endpoint.h"

namespace EAR {
  namespace Communication {
    /// transmitter endpoint class
    class Transmitter : public Endpoint {	    
    public:
      /// default constructor
      Transmitter(void);      
      /// constructor
      /// @param [in] name - transmitter endpoint name
      Transmitter(const std::string &name);      
      /// destructor
      virtual ~Transmitter();
      /// function that initializes transmitter endpoint
      /// @param [in] config - endpoint configuration
      /// @return true if endpoint is initialized, otherwise false
      virtual bool initialize(const Configuration &config) override;
      /// function that shutdowns transmitter endpoint
      virtual void shutdown(void) override;    
      /// function that send buffer to listener
      /// @remark it is for message whose content is well-known type, character stream 
      /// @param [in] buf - buffer
      /// @return length of data sent if sending is done successfully, otherwise errno
      int32_t send(const std::string &buf);	    
      /// function that send buffer to listener
      /// @param [in] buf - buffer
      /// @param [in] size - buffer size
      /// @return length of data sent if succeed, otherwise errno
      int32_t send(const void *buf, size_t size);

    private:
      /// socket
      int m_sock = -1;
      /// receiver address
      struct sockaddr_in m_remote_addr;
    };
  }
}

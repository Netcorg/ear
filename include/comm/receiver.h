/**
 * @file receiver.h
 * @brief class that provides receiving infrastructure for message transfer
 * Time-stamp: <2024-11-02 23:53:29 boo>
 */

#pragma once

#include <arpa/inet.h>
#include "endpoint.h"

namespace EAR {
  namespace Communication {
    /// receiver endpoint class
    class Receiver : public Endpoint {
    public:
      /// default constructor
      Receiver(void);      
      /// constructor
      /// @param [in] name - receiver endpoint name
      Receiver(const std::string &name);      
      /// destructor
      virtual ~Receiver();
      /// function that initializes receiver endpoint
      /// @param [in] config - endpoint configuration
      /// @return true if endpoint is initialized, otherwise false
      virtual bool initialize(const Configuration &config) override;
      /// function that shutdowns receiver endpoint
      virtual void shutdown(void) override;    
      /// function that receives buffer from the publisher
      /// @param [in] buf - buffer
      /// @param [in|out] size - buffer size
      /// @return size of data received if succeed, otherwise errno
      int32_t receive(void *buf, size_t size);

    private:
      /// socket
      int m_sock = -1;
      /// client address 
      struct sockaddr_in m_local_addr;
      /// size of client address
      socklen_t m_local_addr_len;
    };
  }
}

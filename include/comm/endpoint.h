/**
 * @file endpoint.h
 * @brief base class that provides communication endpoint
 * Time-stamp: <2025-01-09 22:55:28 boo>
 */

#pragma once

#include <string>
#include "comm_util.h"

namespace EAR {
  namespace Communication {
    /// communication state
    enum State {
      /// communication closed, which is default state
      COMM_CLOSED,
      /// open communication
      COMM_OPENED
    };

    /// class Endpoint that refers to receiver or transmitter
    class Endpoint {
    public:
      /// default constructor
      Endpoint(void);
      /// constructor
      /// @param [in] name - endpoint name
      Endpoint(const std::string &name);
      /// destructor
      virtual ~Endpoint();
      /// function that sets endpoint name
      /// @param [in] name - endpoint name
      void setName(const std::string &name);
      /// function that gets endpoint name
      /// @return endpoint name
      const std::string &getName(void) const;
      /// function that gets endpoint state
      /// @return endpoint state
      State getState(void) const;	    
      /// function that initializes endpoint
      /// @param [in] config - endpoint configuration
      /// @return true if endpoint is initialized, otherwise false
      virtual bool initialize(const Configuration &config) = 0;	    
      /// function that shutdowns endpoint
      virtual void shutdown(void) = 0;
	    
    protected:
      /// endpoint state
      State m_state = COMM_CLOSED;

      /// function that checks whether IP addres is valid
      /// @param [in] addr - IP address
      /// @return true if IP address is valid, otherwise false
      bool isValidAddress(std::string addr);

    private:
      /// endpoint name
      std::string m_name;
    };
  }
}

/**
 * @file comm_util.h
 * @brief communication configuration for endpoint
 * Time-stamp: <2024-11-02 23:55:56 boo>
 */

#pragma once

#include <string>
#include <cstdint>

namespace EAR {
  namespace Communication {    
    /// configuration class storing endpoint attributes
    struct Configuration {
      /// IP address
      std::string ip;
      /// port number
      uint16_t port = 0U;
      /// blocking type
      bool is_blocked = false;
      /// timeout in msec for blocking configuration
      uint32_t timeout = 0U;
    };
  }
}

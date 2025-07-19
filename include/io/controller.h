/**
 * @file controller.h
 * @brief class that representing I/O controller
 * @author boo
 */

#pragma once

#include <string>

namespace EAR {
  namespace IO {
    class Controller {
    public:
      /// constructor
      /// @param [in] name - io controller name
      explicit Controller(const std::string &name);  
      /// destructor
      virtual ~Controller();
      /// function that gets name of io controller
      /// @return io controller name
      std::string getName(void) const;
      
      /// function that opens io controller interface
      /// @param [in] param - parameters to open
      /// @return error code
      virtual int32_t open(void *param) = 0;
      /// function that closes io controller interface
      /// @return error code
      virtual int32_t close(void) = 0;	    
      /// function that reads data from io controller interface
      /// @param [out] buf - output buffer read from io controller interface
      /// @param [in] size - buffer size
      /// @return error code
      virtual int32_t read(void *buf, const uint16_t size) = 0;
      /// function that writes data from io controller interface
      /// @param [in] buf - input buffer written to io controller interface
      /// @param [in] size - buffer size
      /// @return error code
      virtual int32_t write(const void *buf, const uint16_t size) = 0;

    private:
      /// io controller name
      std::string m_name;

      // prevent copying or moving io controller
      Controller(const Controller &controller) = delete;
      Controller(const Controller &&controller) = delete;
      Controller &operator=(const Controller &controller) = delete;
      Controller &operator=(const Controller &&controller) = delete;
    };
  }
}

/**
 * @file device.h
 * @brief class that representing device
 * @author boo
 */

#pragma once

#include <string>
#include "controller.h"

namespace EAR {
  namespace IO {
    /// enum state for device
    enum State {
      /// none state for device
      DEV_NONE,
      /// refers to device shutdown
      DEV_SHUTDOWN,
      /// refers to device initialized
      DEV_INITIALIZED
    };

    class Device {
    public:
      /// constructor
      /// @param [in] name - device name
      /// @param [in] model - device model
      /// @param [in] version - device version
      Device(const std::string &name, const std::string &model, const std::string &version);  
      /// destructor
      virtual ~Device();	    
      /// function that gets name of device
      /// @return device name
      std::string getName(void) const;	    
      /// function that gets model of device
      /// @return device model
      std::string getModel(void) const;	    
      /// function that gets version of device
      /// @return device model
      std::string getVersion(void) const;	    
      /// function that gets state of device
      /// @return device state
      State getState(void) const;	    
      /// function that sets controller of the device
      /// @param [in] controller - Controller reference
      void setController(Controller *controller);
      /// function that format device information as string
      /// @return device information
      std::string toString(void) const;
      
      /// function that opens device interface
      /// @return error code
      virtual int32_t initialize(void) = 0;
      /// function that closes device interface
      /// @return error code
      virtual int32_t shutdown(void) = 0;	    
      /// function that reads data from device interface
      /// @param [out] buf - output buffer read from device interface
      /// @param [in] size - buffer size
      /// @return error code
      virtual int32_t receive(void *buf, const uint16_t size) = 0;
      /// function that writes data from device interface
      /// @param [in] buf - input buffer written to device interface
      /// @param [in] size - buffer size
      /// @return error code
      virtual int32_t transmit(const void *buf, const uint16_t size) = 0;
      /// function that configures device interface
      /// @param [in|out] target - target for device interface
      /// @param [in] param - type of parameter that is applied to target
      /// @return error code
      virtual int32_t configure(void *target, const int32_t param) = 0;

    protected:
      /// io device state, explicitly open for manipulation by derived classes
      State m_state = DEV_NONE;
      /// io controller for io device
      Controller *m_controller = nullptr;

    private:
      /// io device name
      std::string m_name;
      /// io device model
      std::string m_model;
      /// io device version number/info
      std::string m_version;

      // prevent copying or moving device
      Device(const Device &dev) = delete;
      Device(const Device &&dev) = delete;
      Device &operator=(const Device &task) = delete;
      Device &operator=(const Device &&task) = delete;
    };
  }
}

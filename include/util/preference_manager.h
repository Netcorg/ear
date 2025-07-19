/**
 * @file preference_manager.h
 * @brief preference manager class that is used to manage preference of system
 * @author boo
 */

#pragma once

#include <map>
#include <cstdint>
#include <string>

namespace EAR {
  namespace Utility {
    class PreferenceManager {
    public:
      /// destructor
      virtual ~PreferenceManager();
      /// function that loads configuration file, and parse fields
      /// @param [in] file_path - configuration file path
      /// @return true if configuration is loaded successfully, otherwise false
      static bool load(const std::string &file_path);
      /// function that gets string field indicated by key
      /// @param [in] key - key in configuration file
      /// @param [out] value - value to key
      /// @return true if the value is get and returned, otherwise false
      static bool get(const std::string &key, std::string &value);
      /// function that gets decimal field indicated by key
      /// @param [in] key - key in configuration file
      /// @param [out] value - value to key
      /// @return true if the value is get and returned, otherwise false
      static bool get(const std::string &key, int32_t &value);
      /// function that gets float field indicated by key
      /// @param [in] key - key in configuration file
      /// @param [out] value - value to key
      /// @return true if the value is get and returned, otherwise false
      static bool get(const std::string &key, float &value);
      /// function that gets boolean field indicated by key
      /// @param [in] key - key in configuration file
      /// @param [out] value - value to key
      /// @return true if the value is get and returned, otherwise false
      static bool get(const std::string &key, bool &value);
    
    private:
      /// map that stores string values
      static std::map<std::string, std::string> m_string_values;
      /// map that stores decimal values
      static std::map<std::string, int32_t> m_decimal_values;
      /// map that stores decimal float values
      static std::map<std::string, float> m_float_values;
      /// map that stores boolean values
      static std::map<std::string, bool> m_boolean_values;

      /// default constructor
      PreferenceManager(void);
      
      // prevent copying or moving preference manager
      PreferenceManager(const PreferenceManager &preference_manager) = delete;
      PreferenceManager(const PreferenceManager &&preference_manager) = delete;
      PreferenceManager &operator=(const PreferenceManager &preference_manager) = delete;
      PreferenceManager &operator=(const PreferenceManager &&preference_manager) = delete;
    };
  } 
}

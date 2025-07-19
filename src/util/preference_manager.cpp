#include <fstream>
#include <sstream>
#include "util/preference_manager.h"
#include "spdlog/spdlog.h"
#include "rapidjson/document.h"

std::map<std::string, std::string> EAR::Utility::PreferenceManager::m_string_values;
std::map<std::string, int32_t> EAR::Utility::PreferenceManager::m_decimal_values;
std::map<std::string, float> EAR::Utility::PreferenceManager::m_float_values;
std::map<std::string, bool> EAR::Utility::PreferenceManager::m_boolean_values;

EAR::Utility::PreferenceManager::PreferenceManager() {
}

EAR::Utility::PreferenceManager::~PreferenceManager() {
}

bool EAR::Utility::PreferenceManager::load(const std::string &file_path) {
  if (0 == file_path.length()) {
    spdlog::error("could not read configuration file path, because the file path is empty");
    return false;
  }

  std::ifstream config_file(file_path);

  if (!config_file.is_open()) {
    spdlog::error("could not open configuration file {}", file_path);
    return false;
  }
  
  std::stringstream buffer;
  rapidjson::Document document;

  buffer << config_file.rdbuf();
  document.Parse(buffer.str().c_str());

  for (rapidjson::Value::ConstMemberIterator it = document.MemberBegin(); document.MemberEnd() != it; ++it) {
    if (it->value.IsString()) {
      m_string_values.insert({it->name.GetString(), document[it->name.GetString()].GetString()});
      spdlog::debug("String value: {}", it->value.GetString());
    }
    else if (it->value.IsInt()) {
      m_decimal_values.insert({it->name.GetString(), document[it->name.GetString()].GetInt()});
      spdlog::debug("Int value: {}", it->value.GetInt());
    }
    else if (it->value.IsInt()) {
      m_float_values.insert({it->name.GetString(), document[it->name.GetString()].GetFloat()});
      spdlog::debug("Float value: {}", it->value.GetFloat());
    }
    else if (it->value.IsBool()) {
      m_boolean_values.insert({it->name.GetString(), document[it->name.GetString()].GetBool()});
      spdlog::debug("Bool value: {}", it->value.GetBool());
    }
    else {
      spdlog::error("could not parse json successfully");
    }
  }
  
  config_file.close();
  
  return true;
}

bool EAR::Utility::PreferenceManager::get(const std::string &key, std::string &value) {
  auto it = m_string_values.find(key);

  if (m_string_values.end() == it) {
    spdlog::warn("could not find string value in the preferences");
    return false;
  }

  value = it->second;  
  return true;
}

bool EAR::Utility::PreferenceManager::get(const std::string &key, int32_t &value) {
  auto it = m_decimal_values.find(key);

  if (m_decimal_values.end() == it) {
    spdlog::warn("could not find decimal value in the preferences");
    return false;
  }

  value = it->second;  
  return true;
}

bool EAR::Utility::PreferenceManager::get(const std::string &key, float &value) {
  auto it = m_float_values.find(key);

  if (m_float_values.end() == it) {
    spdlog::warn("could not find float value in the preferences");
    return false;
  }

  value = it->second;  
  return true;
}

bool EAR::Utility::PreferenceManager::get(const std::string &key, bool &value) {
  auto it = m_boolean_values.find(key);

  if (m_boolean_values.end() == it) {
    spdlog::warn("could not find boolean value in the preferences");
    return false;
  }

  value = it->second;  
  return true;
}

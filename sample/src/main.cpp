#include <string>
#include "sched/scheduler.h"
#include "util/preference_manager.h"
#include "dcu_service.h"
#include "radar_service.h"
#include "location_service.h"
#include "gps_device.h"
#include "serial_controller.h"
#include "spdlog/spdlog.h"

int main(int argc, char **argv) {
  if (2 != argc) {
    spdlog::error("./pipeline-test <config json path>");
    return -1;
  }

  std::string path(argv[1]);

  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("json file path: {}", path);
  
  if (!EAR::Utility::PreferenceManager::load(path)) {
    spdlog::error("could not load configuration json file");
    return -1;
  }

  std::string location_service_1_name;
  std::string location_service_2_name;
  int32_t location_service_1_period;
  int32_t location_service_2_period;
  int32_t location_service_1_offset;
  int32_t location_service_2_offset;
  
  EAR::Utility::PreferenceManager::get("location_service_1_name", location_service_1_name);
  EAR::Utility::PreferenceManager::get("location_service_2_name", location_service_2_name);
  EAR::Utility::PreferenceManager::get("location_service_1_period", location_service_1_period);
  EAR::Utility::PreferenceManager::get("location_service_2_period", location_service_2_period);
  EAR::Utility::PreferenceManager::get("location_service_1_offset", location_service_1_offset);
  EAR::Utility::PreferenceManager::get("location_service_2_offset", location_service_2_offset);
  
  EAR::Schedule::Scheduler scheduler("pipeline");
  DCUService dcu_service("dcu-service");
  RadarService radar_service("radar-service");
  LocationService location_service1(location_service_1_name);
  LocationService location_service2(location_service_2_name);
  GPSDevice gps_dev1("gps-device 1", "1", "1.0.0");
  GPSDevice gps_dev2("gps-device 2", "2", "1.0.0");
  SerialController serial_controller1("ser-ctrl 1");
  SerialController serial_controller2("ser-ctrl 2");

  // set controllers of devices
  gps_dev1.setController(&serial_controller1);
  gps_dev2.setController(&serial_controller2);
  
  // set devices of services
  location_service1.setDevice(&gps_dev1);
  location_service2.setDevice(&gps_dev2);

  scheduler.setType(EAR::Schedule::ST_DETACHED);
  
  if (!scheduler.add(&location_service1, location_service_1_period, location_service_1_offset) ||
      !scheduler.add(&location_service2, location_service_2_period, location_service_2_offset) ||
      !scheduler.add(&radar_service, 5000000U) ||
      !scheduler.add(&dcu_service, 3000000U, 3000000U))
    {
      return -1;
    }

  if (!scheduler.start()) { return -1; }
  std::this_thread::sleep_for(std::chrono::microseconds(13000000));
  if (!scheduler.stop()) { return -1; }
    
  return 0;
}

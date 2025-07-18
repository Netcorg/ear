#include "sched/scheduler.h"
#include "dcu_service.h"
#include "location_service.h"
#include "gps_device.h"
#include "serial_controller.h"
#include "spdlog/spdlog.h"

int main() {
  spdlog::set_level(spdlog::level::debug);
      
  EAR::Schedule::Scheduler scheduler("scheduler");
  DCUService dcu_service("dcu-service");
  LocationService location_service1("location-service 1");
  LocationService location_service2("location-service 2");
  GPSDevice gps_dev1("gps-device 1", "1", "1.0.0");
  GPSDevice gps_dev2("gps-device 2", "2", "1.0.0");
  SerialController serial_controller1("ser-ctrl 1");
  SerialController serial_controller2("ser-ctrl 2");

  EAR::Communication::Configuration config;
    
  config.ip = "127.0.0.1";
  config.port = 10000U;
  config.is_blocked = false;
  config.timeout = 0U;

  gps_dev1.setController(&serial_controller1);
  gps_dev2.setController(&serial_controller2);
  location_service1.setDevice(&gps_dev1);
  location_service2.setDevice(&gps_dev2);

  // we can use same configuration for both receiver and transmitter endpoints
  // if their configuration source or targets are same
  dcu_service.setEndpointConfiguration(config);
  location_service1.setEndpointConfiguration(config);
  location_service2.setEndpointConfiguration(config);

  scheduler.setType(EAR::Schedule::ST_SYNCHED);
  
  if (!scheduler.add(&location_service1, 1000000U, 0U) ||
      !scheduler.add(&location_service2, 2000000U, 0U) ||
      !scheduler.add(&dcu_service, 2000000U, 0U)) {
    return -1;
  }

  if (!scheduler.start()) { return -1; }
  spdlog::info("scheduler running");
  
  if (!scheduler.stop()) { return -1; }
  spdlog::info("schedulers terminated");

  return 0;
}

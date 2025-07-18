#include "sched/scheduler.h"
#include "dcu_service.h"
#include "radar_service.h"
#include "location_service.h"
#include "gps_device.h"
#include "serial_controller.h"
#include "spdlog/spdlog.h"

int main() {
  spdlog::set_level(spdlog::level::debug);
  
  EAR::Schedule::Scheduler scheduler("pipeline");
  DCUService dcu_service("dcu-service");
  RadarService radar_service("radar-service");
  LocationService location_service1("location-service 1");
  LocationService location_service2("location-service 2");
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
  
  if (!scheduler.add(&location_service1, 1000000U, 0U) ||
      !scheduler.add(&location_service2, 1000000U, 0U) ||
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

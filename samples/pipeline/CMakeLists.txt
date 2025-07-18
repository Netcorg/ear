cmake_minimum_required(VERSION 3.15)
project(pipeline-test)

set(SOURCES
  src/dcu_service.cpp
  src/radar_service.cpp
  src/gps_device.cpp
  src/location_service.cpp
  src/serial_controller.cpp
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  spdlog
  ear-io
  ear-comm
  ear-sched
)

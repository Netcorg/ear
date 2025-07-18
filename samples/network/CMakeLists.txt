cmake_minimum_required(VERSION 3.15)
project(network-test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
  src/dcu_service.cpp
  src/gps_device.cpp
  src/location_service.cpp
  src/serial_controller.cpp
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
  include
  ../../include
  ../../externals/spdlog/include
)

target_link_directories(${PROJECT_NAME} PRIVATE
  ../../
  ../../externals/spdlog/build
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  spdlog
  ear
)

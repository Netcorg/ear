cmake_minimum_required(VERSION 3.15)

project(ear-comm
  VERSION 1.0.0
  DESCRIPTION "EAR communication library"
  LANGUAGES CXX
)

set(SOURCES
  endpoint.cpp
  receiver.cpp
  transmitter.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ../../include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  spdlog::spdlog
)

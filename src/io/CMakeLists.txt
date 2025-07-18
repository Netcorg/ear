cmake_minimum_required(VERSION 3.15)

project(ear-io
  VERSION 1.0.0
  DESCRIPTION "EAR input/output library"
  LANGUAGES CXX
)

set(SOURCES
  controller.cpp
  device.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ../../include
)

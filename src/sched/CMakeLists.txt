cmake_minimum_required(VERSION 3.15)

project(ear-sched
  VERSION 2.0.0
  DESCRIPTION "EAR scheduling library"
  LANGUAGES CXX
)

set(SOURCES
  task.cpp
  periodic_task.cpp
  one_shot_task.cpp
  scheduler.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 2
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ../../include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  spdlog::spdlog
)

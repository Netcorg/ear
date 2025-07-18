cmake_minimum_required(VERSION 3.12)
project(ear-comm
  VERSION 1.0.0
  DESCRIPTION "EAR communication library"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(INCLUDE_DIR ../../include)

set(SOURCES
  endpoint.cpp
  receiver.cpp
  transmitter.cpp
)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  spdlog::spdlog
)

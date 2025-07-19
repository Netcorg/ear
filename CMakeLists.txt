cmake_minimum_required(VERSION 3.15)
project(ear
  VERSION 1.0.0
  DESCRIPTION "Embedded Architecture Reference (EAR) library"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_EAR_IO "Build EAR io library" ON)
option(BUILD_EAR_COMM "Build EAR communication library" ON)
option(BUILD_EAR_SCHED "Build EAR scheduling library" ON)
option(BUILD_EAR_UTIL "Build EAR utility library" ON)
option(BUILD_EAR_SAMPLE "Build sample based on EAR" ON)

if (WIN32)
  add_definitions(-D_WIN32_WINNT=0x0A00)
endif()

add_subdirectory(externals/spdlog)
add_subdirectory(externals/rapidjson)

include_directories(
  include
  externals/spdlog/include
  externals/asio/asio/include
  externals/rapidjson/include
)

link_directories(
  externals/spdlog
  externals/rapidjson
)

link_libraries(
  spdlog
  RapidJSON
)

if (BUILD_EAR_IO)
  add_subdirectory(src/io)
endif()

if (BUILD_EAR_COMM)
  add_subdirectory(src/comm)
endif()

if (BUILD_EAR_SCHED)
  add_subdirectory(src/sched)
endif()

if (BUILD_EAR_UTIL)
  add_subdirectory(src/util)
endif()

if (BUILD_EAR_SAMPLE)
  add_subdirectory(sample)
endif()

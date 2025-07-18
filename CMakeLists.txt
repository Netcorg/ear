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

# Initialize an empty list for source files
set(SOURCES)

option(BUILD_EAR_IO "Build EAR I/O library" OFF)
option(BUILD_EAR_COMM "Build EAR Communication library" OFF)
option(BUILD_EAR_SCHED "Build EAR Scheduling library" ON)
option(BUILD_EAR_SAMPLES "Build EAR samples" OFF)

add_subdirectory(externals/spdlog)

if (BUILD_EAR_IO)
  add_subdirectory(src/io)
  #list(APPEND SOURCES $<TARGET_OBJECTS:ear-io>)
endif()

if (BUILD_EAR_COMM)
  add_subdirectory(src/comm)
  #list(APPEND SOURCES $<TARGET_OBJECTS:ear-comm>)
endif()

if (BUILD_EAR_SCHED)
  add_subdirectory(src/sched)
  #list(APPEND SOURCES $<TARGET_OBJECTS:ear-sched>)
endif()

include_directories(
  include
  externals/spdlog/include
)

link_directories(
  externals/spdlog
)

link_libraries(
  spdlog
)

if (BUILD_EAR_SAMPLES)
  add_subdirectory(samples/pipeline)
  add_subdirectory(samples/network)
endif()

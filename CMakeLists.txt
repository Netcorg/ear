cmake_minimum_required(VERSION 3.15)
project(ear VERSION 1.0.0 DESCRIPTION "embedded architecture reference (EAR) library")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SPDLOG_DIR externals/spdlog)
set(INCLUDE_DIR include)

# Initialize an empty list for source files
set(SOURCES)

option(EAR_BUILD_SHARED_LIB "Build shared library for EAR" OFF)
option(EAR_BUILD_IO "Build EAR I/O library" ON)
option(EAR_BUILD_COMM "Build EAR Communication library" ON)
option(EAR_BUILD_SCHED "Build EAR Scheduling library" ON)
option(EAR_BUILD_SAMPLES "Build EAR samples" ON)

include_directories(
  ${SPDLOG_DIR}/include
)

if (EAR_BUILD_IO)
  add_subdirectory(src/io)
  list(APPEND SOURCES $<TARGET_OBJECTS:ear-io>)
endif(EAR_BUILD_IO)

if (EAR_BUILD_COMM)
  add_subdirectory(src/comm)
  list(APPEND SOURCES $<TARGET_OBJECTS:ear-comm>)
endif (EAR_BUILD_COMM)

if (EAR_BUILD_SCHED)
  add_subdirectory(src/sched)
  list(APPEND SOURCES $<TARGET_OBJECTS:ear-sched>)
endif (EAR_BUILD_SCHED)

if (EAR_BUILD_SHARED_LIB)
  add_library(${PROJECT_NAME} SHARED ${SOURCES})
else ()
  add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif(EAR_BUILD_SHARED_LIB)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
)

add_subdirectory(${SPDLOG_DIR} ${SPDLOG_DIR}/build)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${INCLUDE_DIR}
)

target_link_directories(${PROJECT_NAME} PRIVATE
  ${SPDLOG_DIR}/build
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  spdlog
)

if (EAR_BUILD_SAMPLES)
  add_subdirectory(samples/pipeline)
  add_subdirectory(samples/network)
endif (EAR_BUILD_SAMPLES)

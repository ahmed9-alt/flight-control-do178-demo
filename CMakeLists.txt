cmake_minimum_required(VERSION 3.20)
project(FlightControl LANGUAGES C)

# Use C99 consistently
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Optionally enable extra warnings
option(ENABLE_WARNINGS "Enable extra compiler warnings" ON)
if(ENABLE_WARNINGS)
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif()
endif()

# Coverage flags are passed in by CI; keep local builds clean.
# If you want local coverage: cmake -DENABLE_COVERAGE=ON ..
option(ENABLE_COVERAGE "Enable coverage flags for local builds" OFF)
if(ENABLE_COVERAGE)
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
  endif()
endif()

# Make headers in src/ visible to tests
include_directories(${CMAKE_SOURCE_DIR}/src)

# Enable CTest and add subdirs
enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

# Build a static library from your source files
add_library(flight_control STATIC
  pid_controller.c
  sensor_stub.c
  actuator_stub.c
)

target_include_directories(flight_control PUBLIC ${CMAKE_SOURCE_DIR}/src)

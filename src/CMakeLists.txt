# src/CMakeLists.txt
add_library(flight_control STATIC
  pid_controller.c
  sensor_stub.c
  actuator_stub.c
)

target_include_directories(flight_control PUBLIC ${CMAKE_SOURCE_DIR}/src)

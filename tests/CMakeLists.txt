# Adjust these if you used submodule vs single-file vendoring:
set(UNITY_SRC ${CMAKE_SOURCE_DIR}/third_party/unity/src/unity.c)
set(UNITY_INC ${CMAKE_SOURCE_DIR}/third_party/unity/src)

# If you vendored single files, use:
# set(UNITY_SRC ${CMAKE_SOURCE_DIR}/third_party/unity/unity.c)
# set(UNITY_INC ${CMAKE_SOURCE_DIR}/third_party/unity)

include_directories(${UNITY_INC})

# Define the test executable from your test files + Unity
add_executable(tests_runner
  test_pid.c
  ${UNITY_SRC}
)

target_link_libraries(tests_runner PRIVATE flight_control)

# Register with CTest
add_test(NAME unit_tests COMMAND tests_runner)

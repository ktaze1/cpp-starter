find_package(Catch2 REQUIRED)

# Unit tests
file(GLOB_RECURSE UNIT_TEST_SOURCES "unit/src/*.cpp" "unit/common-lib/*.cpp" "${CMAKE_SOURCE_DIR}/src/project.cpp")

add_executable(UnitTests ${UNIT_TEST_SOURCES})
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/common-lib)

target_link_libraries(UnitTests PRIVATE common_lib Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(UnitTests)

# Fuzz tests
option(ENABLE_FUZZING "Enable fuzz testing" OFF)
if(ENABLE_FUZZING)
  # Add fuzz testing engine (e.g. LibFuzzer)
  # ...

  file(GLOB_RECURSE FUZZ_TEST_SOURCES "fuzz/src/*.cpp" "fuzz/common-lib/*.cpp")
  add_executable(FuzzTests ${FUZZ_TEST_SOURCES})
  target_link_libraries(FuzzTests PRIVATE common_lib FuzzingEngine)

  # Add a custom target to discover and run the fuzz tests
  add_custom_target(runFuzzTests COMMAND FuzzTests)
endif()

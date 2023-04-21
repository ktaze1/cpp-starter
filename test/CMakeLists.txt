find_package(Catch2 REQUIRED)

add_executable(testMain testMain.cpp)

target_link_libraries(testMain PRIVATE common_lib Catch2::Catch2WithMain)

include(CTest)
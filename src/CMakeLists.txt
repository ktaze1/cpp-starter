add_executable(main project.cpp project.h main.cpp)

target_link_libraries(main PRIVATE common_lib)

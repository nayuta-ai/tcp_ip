cmake_minimum_required(VERSION 3.13)
project(test_example_project)
find_package(GTest)
include_directories(
    ../platform/linux
    ../
)

add_library(source
    ../driver/dummy.c
    ../net.c
    ../util.c
    ../platform/linux/intr.c
)

add_executable(dummy_test dummy_test.cpp)
add_executable(net_test net_test.cpp)
add_executable(net_run_test net_run_test.cpp)
add_executable(intr_test intr_test.cpp)

foreach(target dummy_test net_test net_run_test intr_test)
    target_link_libraries(${target} ${GTEST_BOTH_LIBRARIES} pthread source)
    target_include_directories(${target} PUBLIC ${GTEST_INCLUDE_DIRS})
endforeach()
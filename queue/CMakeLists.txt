cmake_minimum_required(VERSION 3.22)

project(queue)

enable_testing()

file(GLOB SRC_FILES *.cpp)

add_executable(test_queue ${SRC_FILES})
target_link_libraries(test_queue gtest_main gmock)

add_test(NAME test_queue COMMAND test_queue)
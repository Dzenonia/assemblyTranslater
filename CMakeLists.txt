cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
project(new)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)


FetchContent_MakeAvailable(googletest)

file(GLOB SRC_FILES *.cpp)
add_executable(new ${SRC_FILES})
target_link_libraries(new gtest_main gmock)

add_test(NAME new COMMAND new)

cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
project(new)

include(cmake/BuildConfig.cmake)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

FetchContent_MakeAvailable(googletest)

include(FetchContent)
FetchContent_Declare(
        spdlog
        URL https://github.com/gabime/spdlog/archive/refs/heads/v1.x.zip
)

FetchContent_MakeAvailable(spdlog)

include(cmake/ClangTidyCheck.cmake)

add_subdirectory(queue)
add_subdirectory(read)

file(GLOB SRC_FILES *.cpp)
add_executable(new ${SRC_FILES} read/read.cpp)
target_link_libraries(new gtest_main gmock spdlog)

add_test(NAME new COMMAND new)

cmake_minimum_required(VERSION 3.5.1)
project(stopwatch)

set(CMAKE_CXX_STANDARD 11)
set(stopwatch_VERSION_MAJOR 1)
set(stopwatch_VERSION_MINOR 0)

configure_file(
"${PROJECT_SOURCE_DIR}/stopwatchConfig.hpp.in"
"${PROJECT_BINARY_DIR}/stopwatchConfig.hpp"
)

include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include")

file(GLOB SOURCES "src/*.cpp")

add_executable(stopwatch "${SOURCES}")
cmake_minimum_required(VERSION 3.10)

project(ezCalculator)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SRC_LIST ./src/*.c)

include_directories(./include)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(ezCalculator ${SRC_LIST})
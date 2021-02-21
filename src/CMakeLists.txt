cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Logger)
include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_executable(Logger LoggerImpl Logger main)
target_link_libraries(Logger PUBLIC pthread)

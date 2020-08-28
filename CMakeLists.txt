cmake_minimum_required(VERSION 3.10)
project(Hexedit)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)
include_directories(lib/include)
file(GLOB SOURCES src/*.cpp)

add_executable(hexedit ${SOURCES})
target_link_libraries(hexedit curses)
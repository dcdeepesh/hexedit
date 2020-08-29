cmake_minimum_required(VERSION 3.10)
project(Hexedit)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)
if (WIN32)
    include_directories(lib/include)
endif()
file(GLOB SOURCES src/*.cpp src/**/*.cpp)

add_executable(hexedit ${SOURCES})
target_link_libraries(hexedit curses)
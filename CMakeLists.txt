cmake_minimum_required(VERSION 3.0)

project(dbvoyage CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

find_package(pugixml REQUIRED)

add_executable(main main.cpp parser.hpp)

target_link_libraries(main pugixml)

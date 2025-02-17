cmake_minimum_required(VERSION 3.16..)
project(mutuali_information)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Wpedantic -Werror")

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
endif()

add_subdirectory(
    ./local/src/
    )
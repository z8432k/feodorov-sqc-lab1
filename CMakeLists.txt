cmake_minimum_required(VERSION 3.12)
project(feodorov-sqc-lab1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_COMPILER_IS_GNUCC)
    message(STATUS "Detected GNU С compiler. Using specific flags.")
    set(CMAKE_C_FLAGS "-pipe -Wno-unused-parameter")
    set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -Wpedantic -O0 -ggdb3  --coverage")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "-pipe -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wpedantic -O0 -ggdb3 --coverage")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

include_directories("include")

find_package(GSL REQUIRED)

add_library(gauss gauss.c)

add_executable(lab1 main.c)
target_link_libraries(lab1 GSL::gsl gauss)

enable_testing()
add_subdirectory(test)

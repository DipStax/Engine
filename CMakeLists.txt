cmake_minimum_required(VERSION 3.24)

project(FullEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

include(Engine.cmake)
include(TestCore_build.cmake)
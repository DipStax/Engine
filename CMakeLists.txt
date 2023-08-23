cmake_minimum_required(VERSION 3.24)

project(FullEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

function(lib_exist _lib _msg)
    if(NOT DEFINED ${_lib}_LIB)
        message(FATAL_ERROR ${_lib} " library not found: " ${_msg})
    endif()
endfunction(lib_exist)


include(TestCore_build.cmake)
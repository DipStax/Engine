cmake_minimum_required(VERSION 3.24)

project(Tester)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

file(GLOB_RECURSE SRC
    src/**.cpp
    include/**.hpp
    include/**.inl
)

add_executable(Event-dispatcher
    ${SRC}
)

target_include_directories(Event-dispatcher PRIVATE include)

foreach(file IN LISTS SRC_FILE + HDR_FILE)
    get_filename_component(file_path "${file}" PATH)
    string(REPLACE "/" "\\" file_path_msvc "${file_path}")
    source_group("${file_path_msvc}" FILES "${file}")
endforeach()

# General configuration
if (MSVC)
    add_compile_options(/W4 /Werr)
else ()
    add_compile_options(-Wall -Wextra -g3)
endif ()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Event-dispatcher)
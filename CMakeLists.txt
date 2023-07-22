cmake_minimum_required(VERSION 3.24)

project(ECS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

file(GLOB_RECURSE SRC
    src/**.cpp
    include/**.hpp
    include/**.inl
)

add_executable(Core
    ${SRC}
)

target_include_directories(Core PRIVATE include)

foreach(file IN LISTS SRC_FILE + HDR_FILE)
    get_filename_component(file_path "${file}" PATH)
    string(REPLACE "/" "\\" file_path_msvc "${file_path}")
    source_group("${file_path_msvc}" FILES "${file}")
endforeach()

# General configuration
if (MSVC)
    target_compile_options(Core PRIVATE /W4)
    target_compile_definitions(Core PUBLIC NOMINMAX)
else ()
    target_compile_options(Core PRIVATE -Wall -Wextra -g3) # isn't support for now
endif ()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Core)
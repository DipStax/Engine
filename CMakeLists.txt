cmake_minimum_required(VERSION 3.24)

project(ECS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

find_package(opengl_system REQUIRED PATHS build)
find_package(sfml REQUIRED PATHS build)

file(GLOB_RECURSE SRC
    src/**.cpp
    include/**.hpp
    include/**.inl
)

add_executable(Core
    ${SRC}
)

target_include_directories(Core PRIVATE include)
target_link_libraries(Core PRIVATE ${SFML_LIBRARIES})
target_include_directories(Core PRIVATE ${SFML_INCLUDE_DIRS})

target_link_libraries(Core PRIVATE ${CONAN_LIBS})

foreach(file IN LISTS SRC_FILE + HDR_FILE)
    get_filename_component(file_path "${file}" PATH)
    string(REPLACE "/" "\\" file_path_msvc "${file_path}")
    source_group("${file_path_msvc}" FILES "${file}")
endforeach()

# General configuration
if (MSVC)
    add_compile_options(/W4)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
else ()
    add_compile_options(-Wall -Wextra -g3)
endif ()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Core)
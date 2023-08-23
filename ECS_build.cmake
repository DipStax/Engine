include(Engine_build.cmake)

file(GLOB_RECURSE SRC
    src/ECS/**.cpp
    include/ECS/**.hpp
)

add_library(ECS
    ${SRC}
)

target_include_directories(ECS PRIVATE include)

target_link_libraries(ECS PRIVATE ${engine_LIB})

if (MSVC)
    target_compile_options(ECS PRIVATE /W4)
    target_compile_definitions(ECS PUBLIC NOMINMAX)
else ()
    target_compile_options(ECS PRIVATE -Wall -Wextra -g3)
endif ()

set(APPEND ECS_LIB ECS ${engine_LIB})
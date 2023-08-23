file(GLOB_RECURSE SRC_ENGINE
    include/Engine/**.hpp
    src/Engine/**.cpp
    src/Tool/*.cpp
)

add_library(Engine
    ${SRC_ENGINE}
)

target_include_directories(Engine PRIVATE include)

if (MSVC)
    target_compile_options(Engine PRIVATE /W4)
    target_compile_definitions(Engine PUBLIC NOMINMAX)
else ()
    target_compile_options(Engine PRIVATE -Wall -Wextra -g3) # isn't support for now
endif ()

set(APPEND engine_LIB Engine)
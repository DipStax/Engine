file(GLOB_RECURSE SRC_ENGINE
    include/ECS/**.hpp
    include/Engine/**.hpp
    include/Tool/**.hpp
    src/ECS/**.cpp
    src/Engine/**.cpp
    src/Tool/**.cpp
)

add_library(Engine SHARED
    ${SRC_ENGINE}
)

target_include_directories(Engine PRIVATE include)

target_compile_definitions(Engine PUBLIC PROJECT_EXPORTS)

if (MSVC)
    target_compile_options(Engine PRIVATE /W4)
    target_compile_definitions(Engine PUBLIC NOMINMAX)
else ()
    target_compile_options(Engine PRIVATE -Wall -Wextra -g3)
endif ()
include(ECS_build.cmake)

file(GLOB_RECURSE SRC_TESTCORE
    src/*.cpp
    include/*.hpp
)

add_executable(TestCore
    ${SRC_TESTCORE}
)

target_include_directories(TestCore PRIVATE include)

target_link_libraries(TestCore PRIVATE ${ECS_LIB})

if (MSVC)
    target_compile_options(TestCore PRIVATE /W4)
    target_compile_definitions(TestCore PUBLIC NOMINMAX)
else ()
    target_compile_options(TestCore PRIVATE -Wall -Wextra -g3)
endif ()
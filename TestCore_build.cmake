file(GLOB_RECURSE SRC_TESTCORE
    src/Core.cpp
    src/main.cpp
    include/Core.hpp
)

add_executable(TestCore
    ${SRC_TESTCORE}
)

target_include_directories(TestCore PRIVATE include)

target_link_libraries(TestCore PRIVATE Engine)

if (MSVC)
    target_compile_options(TestCore PRIVATE /W4)
    target_compile_definitions(TestCore PUBLIC NOMINMAX)
else ()
    target_compile_options(TestCore PRIVATE -Wall -Wextra -g3)
endif ()
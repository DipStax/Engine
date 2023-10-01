#pragma once

#include <cstdint>

namespace eng::impl::win
{
    struct EventPack
    {
        HWND win;
        uint32_t msg;
        uint64_t wparam;
        int64_t lparam;
    };
}
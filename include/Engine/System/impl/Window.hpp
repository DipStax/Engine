#pragma once

#if defined(WIN32)
    #include "Engine/System/impl/Windows/WEDevice.hpp"
    #include "Engine/System/impl/Windows/WERender.hpp"
    #include "Engine/System/impl/Windows/WindowClass.hpp"
    #include "Engine/System/impl/Windows/EventPack.hpp"
#elif defined(UNIX) || defined(MACOS)
    #include "Engine/System/impl/unix/WindowEvent.hpp"
    #include "Engine/System/impl/unix/WindowCreate.hpp"
    #include "Engine/System/impl/unix/EventPack.hpp"
#else
    static_assert(false, "Platforme not supported");
#endif

namespace eng
{
#if defined(WIN32)
        using WEDevice = impl::win::WEDevice;
        using WERender = impl::win::WERender;
        using WindowClass = impl::win::WindowClass<WEDevice, WERender>;
        using EventPack = impl::win::EventPack;
#elif defined(UNIX) || defined(MACOS)
        using WindowEvent = unix::WindowEvent;
        using WindowCreate = unix::WindowCreate;
        using EventPack = unix::EventPack;
#endif
}
#include <Windows.h>

#include "Engine/System/impl/Windows/WERender.hpp"

namespace eng::impl::win
{
    bool WERender::handle(const EventPack &_ep)
    {
        return handleEvent(_ep);
    }

    void WERender::onDraw(Event _event)
    {
        std::ignore = _event;
    }

    bool WERender::handleEvent(const EventPack &_ep)
    {
        return drawEvent(_ep);
    }

    bool WERender::drawEvent(const EventPack &_ep)
    {
        PAINTSTRUCT ps;
        HDC hdc = nullptr;

        if (_ep.msg == WM_PAINT) {
            hdc = BeginPaint(_ep.win, &ps);
            render(hdc);
            EndPaint(_ep.win, &ps);
            ReleaseDC(_ep.win, hdc);
            return true;
        }
        return false;
    }
}
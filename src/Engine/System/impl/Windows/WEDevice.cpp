#include <Windows.h>
#include <Windowsx.h>

#include "Engine/System/impl/Windows/WEDevice.hpp"

namespace eng::impl::win
{
    bool WEDevice::handle(const EventPack &_ep)
    {
        return handleEvent(_ep);
    }

    bool WEDevice::handleEvent(const EventPack &_ep)
    {
        return focusEvent(_ep) ||
            mouseButtonEvent(_ep) ||
            mouseMoveEvent(_ep) ||
            keyboardEvent(_ep) ||
            resizeEvent(_ep);
    }

    void WEDevice::onFocus(Event _event)
    {
        std::ignore = _event;
    }

    void WEDevice::onMouseButton(Event _event)
    {
        std::ignore = _event;
    }

    void WEDevice::onMouseMove(Event _event)
    {
        std::ignore = _event;
    }

    void WEDevice::onKeyboard(Event _event)
    {
        std::ignore = _event;
    }

    void WEDevice::onResize(Event _event)
    {
        std::ignore = _event;
    }

    bool WEDevice::focusEvent(const EventPack &_ep)
    {
        Event ev{};

        ev.type = Event::Type::Focus;
        switch (_ep.msg) {
            case WM_SETFOCUS:
                ev.focus.state = true;
                break;
            case WM_KILLFOCUS:
                ev.focus.state = false;
                break;
            default:
                return false;
        }
        onFocus(ev);
        return true;
    }

    bool WEDevice::mouseButtonEvent(const EventPack &_ep)
    {
        Event ev{};

        ev.type = Event::Type::MouseButton;
        switch (_ep.msg) {
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_LBUTTONDOWN:
            case WM_XBUTTONDOWN:
                ev.mouseButton.state = Mouse::State::Press;
                break;
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
            case WM_LBUTTONUP:
            case WM_XBUTTONUP:
                ev.mouseButton.state = Mouse::State::Release;
                break;
            case WM_RBUTTONDBLCLK:
            case WM_LBUTTONDBLCLK:
            case WM_MBUTTONDBLCLK:
            case WM_XBUTTONDBLCLK:
                ev.mouseButton.state = Mouse::State::DoubleClick;
                break;
            default:
                return false;
        }
        ev.mouseButton.button = priv::mouseButtonConvert(_ep.wparam);
        onMouseButton(ev);
        return true;
    }

    bool WEDevice::mouseMoveEvent(const EventPack &_ep)
    {
        Event ev{};

        ev.type = Event::Type::MouseMove;
        switch (_ep.msg) {
            case WM_MOUSEMOVE:
                break;
            default:
                return false;
        }
        ev.mouseMove.x = GET_X_LPARAM(_ep.lparam);
        ev.mouseMove.y = GET_Y_LPARAM(_ep.lparam);
        onMouseMove(ev);
        return true;
    }

    bool WEDevice::keyboardEvent(const EventPack &_ep)
    {
        Event ev{};

        ev.type = Event::Type::Keyboard;
        switch (_ep.msg) {
            case WM_KEYDOWN:
                ev.keyboard.state = KeyState::Down;
                break;
            case WM_KEYUP:
                ev.keyboard.state = KeyState::Up;
                break;
            default:
                return false;
        }
        ev.keyboard.key = toKey(_ep.wparam);
        ev.keyboard.control = getKeyState(Key::Control);
        ev.keyboard.alt = getKeyState(Key::Alt);
        ev.keyboard.shift = getKeyState(Key::Shift);
        onKeyboard(ev);
        return true;
    }

    bool WEDevice::resizeEvent(const EventPack &_ep)
    {
        Event ev{};

        ev.type = Event::Type::Resize;
        if (_ep.msg != WM_SIZE || _ep.wparam == SIZE_MAXHIDE || _ep.wparam == SIZE_MAXSHOW)
            return false;
        ev.resize.height = HIWORD(_ep.lparam);
        ev.resize.width = LOWORD(_ep.lparam);
        onResize(ev);
        return true;
    }
}
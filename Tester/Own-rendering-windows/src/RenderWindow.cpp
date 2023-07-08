#include <map>

#include "RenderWindow.hpp"

namespace tester
{
    RenderWindow::RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title)
        : Window(_x, _y, _title)
    {
        m_renderData.resize(_x * _y * 3, 0);
    }

    bool RenderWindow::pollEvent(Event &_event)
    {
        using MsgFn = bool (RenderWindow::*)(size_t, uint32_t, Event &);

        static std::map<size_t, MsgFn> mapfn = {
            { WM_LBUTTONUP, &RenderWindow::eventMouseUp },
            { WM_MBUTTONUP, &RenderWindow::eventMouseUp },
            { WM_RBUTTONUP, &RenderWindow::eventMouseUp },
            { WM_LBUTTONDOWN, &RenderWindow::eventMouseDown },
            { WM_MBUTTONDOWN, &RenderWindow::eventMouseDown },
            { WM_RBUTTONDOWN, &RenderWindow::eventMouseDown },
        };
        MSG msg;

        while (peekMessage(&msg)) {
            if (mapfn.contains(msg.message))
                if ((this->*(mapfn[msg.message]))(msg.lParam, msg.wParam, _event))
                    return true;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return false;
    }

    Point2<uint32_t> RenderWindow::getSize() const
    {
        return Window::getSize();
    }

    void RenderWindow::display() const
    {
        SendMessage(getWindow(), WM_PAINT, 0, 0);
    }

    void RenderWindow::clear()
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        ret = invalideRect(&rect);
        // error handling with ret
    }

    void RenderWindow::render() const
    {
        Point2<uint32_t> size = getSize();
        BITMAPINFO bmi;

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = size.x;
        bmi.bmiHeader.biHeight = -size.y;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 24;
        bmi.bmiHeader.biCompression = BI_RGB;
        SetDIBitsToDevice(getDc(), 0, 0, size.x, size.y, 0, 0, 0, size.y, m_renderData.data(), &bmi, DIB_RGB_COLORS);
    }

    bool RenderWindow::eventMouseUp(size_t _param, uint32_t _eparam, Event& _event)
    {
        _event.type = Event::Type::MouseButton;

        _event.mouseButton.press = false;
        if (_param == WM_LBUTTONUP)
            _event.mouseButton.button = Mouse::Button::Left;
        else if (_param == WM_MBUTTONUP)
            _event.mouseButton.button = Mouse::Button::Left;
        else if (_param == WM_RBUTTONUP)
            _event.mouseButton.button = Mouse::Button::Left;
        else
            return false;
        return true;
    }

    bool RenderWindow::eventMouseDown(size_t _param, uint32_t _eparam, Event& _event)
    {
        _event.type = Event::Type::MouseButton;

        _event.mouseButton.press = true;
        if (_param == WM_LBUTTONDOWN)
            _event.mouseButton.button = Mouse::Button::Left;
        else if (_param == WM_MBUTTONDOWN)
            _event.mouseButton.button = Mouse::Button::Left;
        else if (_param == WM_RBUTTONDOWN)
            _event.mouseButton.button = Mouse::Button::Left;
        else
            return false;
        return true;
    }
}
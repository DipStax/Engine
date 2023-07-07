#include <map>

#include "RenderWindow.hpp"

namespace tester
{
    RenderWindow::RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title)
        : Window(_x, _y, _title)
    {
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

        while (peekMessage(&msg))
            if (mapfn.contains(msg.message))
                return (this->*(mapfn[msg.message]))(msg.lParam, msg.wParam, _event);
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        return false;
    }

    void RenderWindow::clear()
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        ret = invalideRect(&rect);
        // error handling with ret
    }

    bool RenderWindow::draw(const IDrawable &_elem)
    {
        _elem.draw(*this);
        return true;
    }

    bool RenderWindow::draw(const Pixel *_pos, size_t _size, Vertex::Type _type)
    {
        COLORREF clr;
        bool ret = false;

        if (_type == Vertex::Type::Pixel) {
            for (size_t it = 0; it < _size; it++) {
                clr = RGB(_pos[it].clr.R, _pos[it].clr.G, _pos[it].clr.B);
                ret = setPixel(_pos[it].pos.x, _pos[it].pos.y, clr);
            }
        } else if (_type == Vertex::Type::Line) {
            ret = penMove(_pos[0].pos.x, _pos[0].pos.y, NULL);
            if (!ret)
                return ret;
            for (size_t it = 1; it < _size; it++)
                ret = lineTo(_pos[it].pos.x, _pos[it].pos.y);
            if (_type == Vertex::Type::Polygone || !ret)
                lineTo(_pos[0].pos.x, _pos[0].pos.y);
        }
        return ret;
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
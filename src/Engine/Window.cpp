#include <map>
#include <iostream>

#include "Engine/Window.hpp"

namespace Win
{
    HWND find(LPCTSTR _name, LPCTSTR _class)
    {
        return FindWindow(_class, _name);
    }
}

namespace eng
{
    Window::Window(uint32_t _x, uint32_t _y, const std::string& _title)
    {
        open(_x, _y, _title);
    }

    Window::~Window()
    {
        close();
    }

    void Window::open(uint32_t _x, uint32_t _y, const std::string& _title)
    {
        if (m_open)
            close();
        m_winClass = {
                .lpfnWndProc = WIN_proc,
                .hInstance = GetModuleHandle(NULL),
                .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
                .lpszClassName = WIN_className,
        };
        RegisterClass(&m_winClass);
        m_win = CreateWindowEx(0, WIN_className, _title.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, _x, _y, NULL, NULL, m_winClass.hInstance, this
        );
        m_dc = getDc();
        m_open = true;
    }

    bool Window::isOpen() const
    {
        return m_open;
    }

    void Window::setTitle(const std::string& _title)
    {
        bool ret = SetWindowText(m_win, _title.c_str());

        // error handling with ret
    }

    std::string Window::getTitle() const
    {
        std::string title(WIN_MAXTITLE, '\0');
        int ret = GetWindowText(m_win, const_cast<char*>(title.c_str()), WIN_MAXTITLE);

        // error handling with ret
        return title;
    }

    void Window::move(uint32_t _x, int32_t _y)
    {
        Point2<uint32_t> pos = getPosition();

       setPosition(pos.x + _y, pos.y + _y);
    }

    void Window::setPosition(uint32_t _x, uint32_t _y)
    {
        Point2<uint32_t> size = Window::getSize();
        bool ret = move(size.x, size.y, _x, _y);

        // error handling with ret
    }

    Point2<uint32_t> Window::getPosition() const
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        return Point2<uint32_t>{ static_cast<uint32_t>(rect.left), static_cast<uint32_t>(rect.top) };
    }

    void Window::setSize(uint32_t _x, uint32_t _y)
    {
        Point2<uint32_t> pos = Window::getPosition();
        bool ret = move(_x, _y, pos.x, pos.y);

        // error handling with ret
    }

    Point2<uint32_t> Window::getSize() const
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        return Point2<uint32_t>{ static_cast<uint32_t>(rect.right - rect.left), static_cast<uint32_t>(rect.bottom - rect.top) };
    }

    bool Window::pollEvent(Event &_event)
    {
        using MsgFn = bool (Window::*)(size_t, uint32_t, Event &);

        static std::map<size_t, MsgFn> mapfn = {};
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

    void Window::close()
    {
        ReleaseDC(m_win, m_dc);
        DestroyWindow(m_win);
        m_open = false;
    }

    HWND Window::getWindow() const
    {
        return m_win;
    }

    LRESULT CALLBACK Window::WIN_proc(HWND _win, UINT _msg, WPARAM _wparam, LPARAM _lparam)
    {
        PAINTSTRUCT ps;
        Window *pthis;

        if (_msg == WM_NCCREATE) {
            CREATESTRUCT* create = (CREATESTRUCT*)_lparam;

            pthis = (Window *)create->lpCreateParams;
            SetWindowLongPtr(_win, GWLP_USERDATA, (LONG_PTR)pthis);
        } else {
            pthis = (Window *)GetWindowLongPtr(_win, GWLP_USERDATA);
        }
        switch (_msg) {
            case WM_PAINT: {
                HDC hdc = BeginPaint(_win, &ps);
                pthis->render(hdc);
                EndPaint(_win, &ps);
            }
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                pthis->close();
                break;
            default:
                return DefWindowProc(_win, _msg, _wparam, _lparam);
        }

        return 0;
    }

    HDC Window::getDc() const
    {
        return m_dc;
    }

    bool Window::peekMessage(LPMSG _msg) const
    {
        return PeekMessage(_msg, m_win, 0, 0, PM_REMOVE);
    }

    bool Window::winRect(LPRECT _rect) const
    {
        return GetWindowRect(m_win, _rect);
    }

    bool Window::move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const
    {
        return MoveWindow(m_win, _x, _y, _width, _height, true);
    }
}
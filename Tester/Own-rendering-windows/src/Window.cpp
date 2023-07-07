#include <iostream>

#include "Window.hpp"

namespace Win
{
    HWND find(LPCTSTR _name, LPCTSTR _class)
    {
        return FindWindow(_class, _name);
    }
}

namespace tester
{
    Window::Window(uint32_t _x, uint32_t _y, const std::string& _title)
    {
        m_winClass = {
                .lpfnWndProc = WIN_proc,
                .hInstance = GetModuleHandle(NULL),
                .hIcon = LoadIcon(NULL, IDI_APPLICATION),
                .hCursor = LoadCursor(NULL, IDC_ARROW),
                .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
                .lpszClassName = WIN_className,
        };
        RegisterClass(&m_winClass);
        m_win = CreateWindowEx(0, WIN_className, _title.c_str(), WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, _x, _y, NULL, NULL, m_winClass.hInstance, NULL
        );
        if (m_win != NULL) {
            ShowWindow(m_win, SW_SHOWDEFAULT);
        }
        m_dc = getDc();
    }

    Window::~Window()
    {
        releaseDC();
    }

    void Window::setTitle(const std::string& _title)
    {
        if (!SetWindowText(m_win, _title.c_str())) {
            std::cerr << "Window: can't change the title of the window" << std::endl;
        }
    }

    std::string Window::getTitle() const
    {
        std::string title(WIN_MAXTITLE, '\0');
        int ret = GetWindowText(m_win, const_cast<char*>(title.c_str()), WIN_MAXTITLE);

        // error handling with ret
        return title;
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

    LRESULT CALLBACK Window::WIN_proc(HWND _win, UINT _msg, WPARAM wParam, LPARAM lParam)
    {
        static HDC hDC;
        static HPEN hPen;
        static HBRUSH hBrush;
        PAINTSTRUCT ps;

        switch (_msg) {
        case WM_CREATE:
            hDC = GetDC(_win);
            break;
        case WM_PAINT:
            BeginPaint(_win, &ps);
            EndPaint(_win, &ps);
            break;
            case WM_DESTROY:
                ReleaseDC(_win, hDC);
                DeleteObject(hPen);
                DeleteObject(hBrush);
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(_win, _msg, wParam, lParam);
        }

        return 0;
    }

    bool Window::peekMessage(LPMSG _msg) const
    {
        return PeekMessage(_msg, m_win, 0, 0, PM_REMOVE);
    }

    HDC Window::getDc() const
    {
        return GetDC(m_win);
    }

    int Window::releaseDC() const
    {
        return ReleaseDC(m_win, m_dc);
    }

    bool Window::penMove(uint32_t _x, uint32_t _y, LPPOINT _lpoint)
    {
        return MoveToEx(m_dc, _x, _y, _lpoint);
    }

    bool Window::winRect(LPRECT _rect) const
    {
        return GetWindowRect(m_win, _rect);
    }

    bool Window::move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const
    {
        return MoveWindow(m_win, _x, _y, _width, _height, true);
    }

    bool Window::invalideRect(const LPRECT _rect)
    {
        return InvalidateRect(m_win, _rect, false);
    }

    COLORREF Window::setPixel(uint32_t _x, uint32_t _y, COLORREF _clr)
    {
        return SetPixel(m_dc, _x, _y, _clr);
    }

    COLORREF Window::getPixel(uint32_t _x, uint32_t _y)
    {
        return GetPixel(m_dc, _x, _y);
    }

    bool Window::lineTo(uint32_t _x, uint32_t _y)
    {
        return LineTo(m_dc, _x, _y);
    }

    bool Window::polyline(const POINT *_lpoint, uint32_t _count)
    {
        return Polyline(m_dc, _lpoint, _count);
    }

    bool Window::polylineTo(const POINT *_lpoint, uint32_t _count)
    {
        return Polyline(m_dc, _lpoint, _count);
    }

    bool Window::polyBezier(const POINT *_lpoint, uint32_t _count)
    {
        return PolyBezier(m_dc, _lpoint, _count);
    }

    bool Window::polyBezierTo(const POINT *_lpoint, uint32_t _count)
    {
        return PolyBezierTo(m_dc, _lpoint, _count);
    }
}
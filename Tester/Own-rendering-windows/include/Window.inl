#include <iostream>

#include "Window.hpp"

namespace tester
{
    template<class T>
    Window<T>::Window(uint32_t _x, uint32_t _y, const std::string& _title)
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

    template<class T>
    Window<T>::~Window()
    {
        releaseDC();
    }

    template<class T>
    void Window<T>::setTitle(const std::string& _title)
    {
        if (!SetWindowText(m_win, _title.c_str())) {
            std::cerr << "Window: can't change the title of the window" << std::endl;
        }
    }

    template<class T>
    std::string Window<T>::getTitle() const
    {
        std::string title(WIN_MAXTITLE, '\0');
        int ret = GetWindowText(m_win, const_cast<char*>(title.c_str()), WIN_MAXTITLE);

        // error handling with ret
        return title;
    }

    template<class T>
    void Window<T>::setPosition(uint32_t _x, uint32_t _y)
    {
        Point2<uint32_t> size = Window<T>::getSize();
        bool ret = move(size.x, size.y, _x, _y);

        // error handling with ret
    }

    template<class T>
    Point2<uint32_t> Window<T>::getPosition() const
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        return Point2<uint32_t>{ static_cast<uint32_t>(rect.left), static_cast<uint32_t>(rect.top) };
    }

    template<class T>
    void Window<T>::setSize(uint32_t _x, uint32_t _y)
    {
        Point2<uint32_t> pos = Window<T>::getPosition();
        bool ret = move(_x, _y, pos.x, pos.y);

        // error handling with ret
    }

    template<class T>
    Point2<uint32_t> Window<T>::getSize() const
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        return Point2<uint32_t>{ static_cast<uint32_t>(rect.right - rect.left), static_cast<uint32_t>(rect.bottom - rect.top) };
    }

    template<class T>
    LRESULT CALLBACK Window<T>::WIN_proc(HWND _win, UINT _msg, WPARAM _wparam, LPARAM _lparam)
    {
        HDC hDC;
        PAINTSTRUCT ps;
        T *pthis;

        if (_msg == WM_NCCREATE) {
            CREATESTRUCT* create = (CREATESTRUCT*)_lparam;

            pthis = (T *)create->lpCreateParams;
            SetWindowLongPtr(_win, GWLP_USERDATA, (LONG_PTR)pthis);
        } else {
            pthis = (T*)GetWindowLongPtr(_win, GWLP_USERDATA);
        }
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
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(_win, _msg, _wparam, _lparam);
        }

        return 0;
    }

    template<class T>
    bool Window<T>::peekMessage(LPMSG _msg) const
    {
        return PeekMessage(_msg, m_win, 0, 0, PM_REMOVE);
    }

    template<class T>
    HDC Window<T>::getDc() const
    {
        return GetDC(m_win);
    }

    template<class T>
    int Window<T>::releaseDC() const
    {
        return ReleaseDC(m_win, m_dc);
    }

    template<class T>
    bool Window<T>::penMove(uint32_t _x, uint32_t _y, LPPOINT _lpoint)
    {
        return MoveToEx(m_dc, _x, _y, _lpoint);
    }

    template<class T>
    bool Window<T>::winRect(LPRECT _rect) const
    {
        return GetWindowRect(m_win, _rect);
    }

    template<class T>
    bool Window<T>::move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const
    {
        return MoveWindow(m_win, _x, _y, _width, _height, true);
    }

    template<class T>
    bool Window<T>::invalideRect(const LPRECT _rect)
    {
        return InvalidateRect(m_win, _rect, false);
    }

    template<class T>
    COLORREF Window<T>::setPixel(uint32_t _x, uint32_t _y, COLORREF _clr)
    {
        return SetPixel(m_dc, _x, _y, _clr);
    }

    template<class T>
    COLORREF Window<T>::getPixel(uint32_t _x, uint32_t _y)
    {
        return GetPixel(m_dc, _x, _y);
    }

    template<class T>
    bool Window<T>::lineTo(uint32_t _x, uint32_t _y)
    {
        return LineTo(m_dc, _x, _y);
    }

    template<class T>
    bool Window<T>::polyline(const POINT *_lpoint, uint32_t _count)
    {
        return Polyline(m_dc, _lpoint, _count);
    }

    template<class T>
    bool Window<T>::polylineTo(const POINT *_lpoint, uint32_t _count)
    {
        return Polyline(m_dc, _lpoint, _count);
    }

    template<class T>
    bool Window<T>::polyBezier(const POINT *_lpoint, uint32_t _count)
    {
        return PolyBezier(m_dc, _lpoint, _count);
    }

    template<class T>
    bool Window<T>::polyBezierTo(const POINT *_lpoint, uint32_t _count)
    {
        return PolyBezierTo(m_dc, _lpoint, _count);
    }
}
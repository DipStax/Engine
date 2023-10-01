#include "Engine/System/impl/Windows/WindowClass.hpp"

namespace eng::impl::win
{
    template<class ...Ts>
    void WindowClass<Ts...>::open(uint32_t _x, uint32_t _y, const std::string& _title)
    {
        if (m_open)
            close();
        m_winClass.style = CS_VREDRAW | CS_DBLCLKS,
        m_winClass.lpfnWndProc = WIN_proc,
        m_winClass.hInstance = GetModuleHandle(NULL),
        m_winClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
        m_winClass.lpszClassName = WIN_className,
        RegisterClass(&m_winClass);
        m_win = CreateWindowEx(0, WIN_className, _title.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, _x, _y, NULL, NULL, m_winClass.hInstance, this
        );
        m_open = true;
    }

    template<class ...Ts>
    void WindowClass<Ts...>::display()
    {
        InvalidateRect(m_win, NULL, FALSE);
    }

    template<class ...Ts>
    void WindowClass<Ts...>::close()
    {
        DestroyWindow(m_win);
        m_open = false;
    }

    template<class ...Ts>
    bool WindowClass<Ts...>::isOpen() const
    {
        return m_open;
    }

    template<class ...Ts>
    void WindowClass<Ts...>::disptachEvent()
    {
        MSG msg;

        while (PeekMessage(&msg, m_win, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    template<class ...Ts>
    LRESULT CALLBACK WindowClass<Ts...>::WIN_proc(HWND _win, UINT _msg, WPARAM _wparam, LPARAM _lparam)
    {
        PAINTSTRUCT ps;
        WindowClass<Ts...> *pthis;
        EventPack ep{ _win, _msg, _wparam, _lparam };

        if (_msg == WM_NCCREATE) {
            CREATESTRUCT* create = (CREATESTRUCT*)_lparam;

            pthis = (WindowClass<Ts...> *)create->lpCreateParams;
            SetWindowLongPtr(_win, GWLP_USERDATA, (LONG_PTR)pthis);
        } else {
            pthis = (WindowClass<Ts...> *)GetWindowLongPtr(_win, GWLP_USERDATA);
        }
        // handle here
        if (WindowClass<Ts...>::CallHandle(*pthis, ep))
            return 0;
        if (_msg != WM_DESTROY)
            return DefWindowProc(_win, _msg, _wparam, _lparam);
        PostQuitMessage(0);
        pthis->close();
        return 0;
    }

    template<class ...Ts>
    template<IsWE _T, class ..._Ts>
    bool WindowClass<Ts...>::CallHandle(_T &_win, const EventPack &_ep)
    {
        return static_cast<_T>(m_win).handle(_ep) || WindowClass<Ts...>::CallHandle<_Ts...>(_win, _ep);
    }

    template<class ...Ts>
    template<IsWE _T>
    static bool WindowClass<Ts...>::CallHandle(_T &_win, const EventPack &_ep)
    {
        return static_cast<_T>(m_win).handle(_ep);
    }

    template<class ...Ts>
    void WindowClass<Ts...>::setTitle(const std::string& _title)
    {
        bool ret = SetWindowText(m_win, _title.c_str());

        // error handling with ret
    }

    template<class ...Ts>
    std::string WindowClass<Ts...>::getTitle() const
    {
        std::string title(256, '\0');
        int ret = GetWindowText(m_win, const_cast<char*>(title.c_str()), 256);

        // error handling with ret
        return title;
    }

    template<class ...Ts>
    void WindowClass<Ts...>::move(uint32_t _x, int32_t _y)
    {
        Point2<uint32_t> pos = getPosition();

       setPosition(pos.x + _x, pos.y + _y);
    }

    template<class ...Ts>
    void WindowClass<Ts...>::setPosition(uint32_t _x, uint32_t _y)
    {
        Point2<uint32_t> size = WindowClass<Ts...>::getSize();
        bool ret = move(size.x, size.y, _x, _y);

        // error handling with ret
    }

    template<class ...Ts>
    Point2<uint32_t> WindowClass<Ts...>::getPosition() const
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        return Point2<uint32_t>{ static_cast<uint32_t>(rect.left), static_cast<uint32_t>(rect.top) };
    }

    template<class ...Ts>
    void WindowClass<Ts...>::setSize(uint32_t _x, uint32_t _y)
    {
        Point2<uint32_t> pos = WindowClass<Ts...>::getPosition();
        bool ret = move(_x, _y, pos.x, pos.y);

        // error handling with ret
    }

    template<class ...Ts>
    Point2<uint32_t> WindowClass<Ts...>::getSize() const
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        return Point2<uint32_t>{ static_cast<uint32_t>(rect.right - rect.left), static_cast<uint32_t>(rect.bottom - rect.top) };
    }

    template<class ...Ts>
    bool WindowClass<Ts...>::winRect(LPRECT _rect) const
    {
        return GetWindowRect(m_win, _rect);
    }

    template<class ...Ts>
    bool WindowClass<Ts...>::move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const
    {
        return MoveWindow(m_win, _x, _y, _width, _height, true);
    }
}
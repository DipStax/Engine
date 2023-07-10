#pragma once

#include <string>
#include <thread>

#include <windows.h>

#include "Engine/Point2.hpp"
#include "Engine/Color.hpp"

#ifndef WIN_MAXTITLE
#define WIN_MAXTITLE 256
#endif

namespace Win
{
    HWND find(LPCTSTR _name, LPCTSTR _class);
}

namespace tester
{
    class Window
    {
        public:
            Window(uint32_t _x, uint32_t _y, const std::string& _title);
            ~Window();

            void setTitle(const std::string& _title);
            [[nodiscard]] std::string getTitle() const;

            //void move(uint32_t _x, int32_t _y);
            void setPosition(uint32_t _x, uint32_t _y);
            [[nodiscard]] Point2<uint32_t> getPosition() const;
            void setSize(uint32_t _x, uint32_t _y);
            [[nodiscard]] Point2<uint32_t> getSize() const;

        protected:
            static constexpr char WIN_className[] = "Sample Window Class";

            static LRESULT CALLBACK WIN_proc(HWND _win, UINT _msg, WPARAM _wparam, LPARAM _lparam);

            bool peekMessage(LPMSG _msg) const;

            [[nodiscard]] HWND getWindow() const;

            [[nodiscard]] HDC getDc() const;
            int releaseDC() const;

            bool penMove(uint32_t _x, uint32_t _y, LPPOINT _lpoint);

            bool winRect(LPRECT _rect) const;
            bool move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const;
            bool invalideRect(const LPRECT _rect);

            COLORREF setPixel(uint32_t _x, uint32_t _y, COLORREF _clr);
            COLORREF getPixel(uint32_t _x, uint32_t _y);

            bool lineTo(uint32_t _x, uint32_t _y);
            bool polyline(const POINT *_lpoint, uint32_t _count);
            bool polylineTo(const POINT *_lpoint, uint32_t _count);
            bool polyBezier(const POINT *_lpoint, uint32_t _count);
            bool polyBezierTo(const POINT *_lpoint, uint32_t _count);

            virtual void render(HDC _draw) const = 0;

        private:
            WNDCLASS m_winClass{};
            HWND m_win;
            HDC m_dc;
    };
}
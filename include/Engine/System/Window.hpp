#pragma once

#include <string>
#include <thread>

#include <windows.h>

#include "Engine/Maths/Point2.hpp"
#include "Engine/Rendering/Color.hpp"
#include "Engine/Event/Event.hpp"

#ifndef WIN_MAXTITLE
    #define WIN_MAXTITLE 256
#endif

namespace eng
{
    class PROJECT_API Window
    {
        public:
            Window(uint32_t _x, uint32_t _y, const std::string& _title);
            ~Window();

            void open(uint32_t _x, uint32_t _y, const std::string& _title);
            [[nodiscard]] bool isOpen() const;

            void setTitle(const std::string& _title);
            [[nodiscard]] std::string getTitle() const;

            void move(uint32_t _x, int32_t _y);
            void setPosition(uint32_t _x, uint32_t _y);
            [[nodiscard]] Point2<uint32_t> getPosition() const;

            void setSize(uint32_t _x, uint32_t _y);
            [[nodiscard]] Point2<uint32_t> getSize() const;


            void close();

        protected:
            void disptachEvent();

            [[nodiscard]] HWND getWindow() const;

            bool resized(uint64_t _lparam, int64_t _wparam, Event &_event);
            virtual void onResize(Event &_event);

        private:
            static LRESULT CALLBACK WIN_proc(HWND _win, UINT _msg, WPARAM _wparam, LPARAM _lparam);

            static constexpr char WIN_className[] = "Sample Window Class";

            [[nodiscard]] HDC getDc() const;

            bool peekMessage(LPMSG _msg) const;
            bool winRect(LPRECT _rect) const;
            bool move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const;

            virtual void render(HDC _draw) const = 0;

            WNDCLASS m_winClass{};
            HWND m_win;
            HDC m_dc;
            bool m_open = false;
    };
}
#pragma once

#include <type_traits>

#include <Windows.h>

#include "Engine/System/impl/Windows/EventPack.hpp"
#include "Engine/System/impl/Interface/IWindowClass.hpp"
#include "Engine/System/impl/Interface/IWIndowEvent.hpp"
#include "Tool/PreProcessing.hpp"

template<class T>
concept IsWE = std::is_base_of<eng::impl::IWindowEvent<T>, T>::value;

namespace eng::impl::win
{
    template<class ...Ts>
    class WindowClass : public IWindowClass, public Ts...
    {
        public:
            void open(uint32_t _x, uint32_t _y, const std::string & _title);

            [[nodiscard]] bool isOpen() const;

            void setTitle(const std::string& _title);
            [[nodiscard]] std::string getTitle() const;

            void move(uint32_t _x, int32_t _y);
            void setPosition(uint32_t _x, uint32_t _y);
            [[nodiscard]] Point2<uint32_t> getPosition() const;

            void setSize(uint32_t _x, uint32_t _y);
            [[nodiscard]] Point2<uint32_t> getSize() const;

            void display();

            void close();

        protected:
            WindowClass() = default;
            ~WindowClass() = default;

            void disptachEvent();

            static LRESULT CALLBACK WIN_proc(HWND _win, UINT _msg, WPARAM _wparam, LPARAM _lparam);

            template<IsWE _T, class ..._TS>
            static bool CallHandle(_T &_win, const EventPack& _ep);
            template<IsWE _T>
            static bool CallHandle(_T &_win, const EventPack& _ep);

        private:
            bool winRect(LPRECT _rect) const;
            bool move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const;

            static constexpr const char *WIN_className = (const char*)"Sample Window Class";

            WNDCLASS m_winClass{};
            HWND m_win;
            bool m_open = false;
    };
}

#include "Engine/System/impl/Windows/WindowClass.inl"
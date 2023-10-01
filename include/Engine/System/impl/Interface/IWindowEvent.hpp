#pragma once

namespace eng::impl
{
    template<class T>
    class IWindowEvent
    {
        protected:
            virtual [[nodiscard]] bool handle(T &_win) = 0;
    };
}
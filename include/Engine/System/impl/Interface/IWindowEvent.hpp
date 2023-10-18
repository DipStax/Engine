#pragma once

namespace eng::impl
{
    class IWindowEvent
    {
        protected:
            friend class IWindowClass;

            virtual [[nodiscard]] bool handle(const win::EventPack &_win) = 0;
    };
}
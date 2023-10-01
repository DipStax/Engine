#pragma once

#include <string>

namespace eng::impl
{
    class IWindowClass
    {
        public:
            virtual void open(uint32_t _x, uint32_t _y, const std::string& _title) = 0;

            virtual void close() = 0;

            virtual [[nodiscard]] bool isOpen() const = 0;

        protected:
            virtual void disptachEvent() = 0;
    };
}
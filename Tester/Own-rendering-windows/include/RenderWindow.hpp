#pragma once

#include "Window.hpp"
#include "Vertex.hpp"
#include "RenderTarget.hpp"

namespace tester
{
    class RenderWindow : public Window, public RenderTarget
    {
        public:
            RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title);
            ~RenderWindow() = default;

            [[nodiscard]] Point2<uint32_t> getSize() const;

            void display() const;

        protected:
            void render(HDC _draw) const;
    };
}
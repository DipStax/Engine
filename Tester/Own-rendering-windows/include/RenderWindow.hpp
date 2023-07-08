#pragma once

#include "Window.hpp"
#include "Vertex.hpp"
#include "Event.hpp"
#include "RenderTarget.hpp"

namespace tester
{
    class RenderWindow : public Window<RenderWindow>, public RenderTarget
    {
        public:
            RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title);
            ~RenderWindow();

            bool pollEvent(Event &_event);
            void clear();

            [[nodiscard]] Point2<uint32_t> getSize() const;

        private:
            bool eventMouseUp(size_t _param, uint32_t _eparam, Event &_event);
            bool eventMouseDown(size_t _param, uint32_t _eparam, Event &_event);
    };
}
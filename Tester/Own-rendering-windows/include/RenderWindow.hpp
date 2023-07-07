#pragma once

#include "Window.hpp"
#include "Vertex.hpp"
#include "Event.hpp"

namespace tester
{
    class RenderWindow : public Window
    {
        public:
            RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title);

            bool pollEvent(Event &_event);
            void clear();

            bool draw(const IDrawable &_elem);
            bool draw(const Pixel *_pos, size_t _size, Vertex::Type _type);

        private:
            bool eventMouseUp(size_t _param, uint32_t _eparam, Event &_event);
            bool eventMouseDown(size_t _param, uint32_t _eparam, Event &_event);
    };
}
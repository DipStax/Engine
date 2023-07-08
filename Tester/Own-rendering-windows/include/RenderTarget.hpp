#pragma once

#include "IDrawable.hpp"
#include "Vertex.hpp"

namespace tester
{
    class RenderTarget
    {
        public:
            virtual void clear() = 0;

            virtual void draw(const IDrawable &_draw);
            virtual void draw(const Pixel *_px, size_t _size, Vertex::Type _type);

            virtual [[nodiscard]] Point2<uint32_t> getSize() const = 0;

        protected:
            RenderTarget() = default;

            Color *m_renderData;

        private:
            void drawPixel(const Pixel &_px);
            void drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec, const Color &_clr);
            // RGB macro pour set avec une COLORREF
    };
}
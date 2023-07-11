#pragma once

#include "IDrawable.hpp"
#include "Vertex.hpp"

#include  <windows.h>

namespace tester
{
    class RenderTarget
    {
        public:
            void create(uint32_t _x, uint32_t _y);

            void draw(const IDrawable &_draw);
            void draw(const Pixel *_px, size_t _size, Vertex::Type _type);

            void clear(const Color &_clr = { 255, 255, 255, 255 });

            virtual [[nodiscard]] Point2<uint32_t> getSize() const = 0;

        protected:
            RenderTarget() = default;

            [[nodiscard]] HBITMAP getDib() const;

        private:
            void drawPixel(const Pixel &_px);
            void drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec, const Color &_clr);

            HBITMAP m_dib;
            uint32_t *m_data = nullptr;
            Point2<uint32_t> m_size;
    };
}
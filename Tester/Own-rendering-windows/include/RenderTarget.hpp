#pragma once

#include  <windows.h>

#include "Engine/Color.hpp"
#include "Image.hpp"
#include "VertexArray.hpp"

namespace tester
{
    class RenderTarget
    {
        public:
            void create(uint32_t _x, uint32_t _y);

            void draw(const IDrawable &_elem, const Image *_img = nullptr);
            void draw(const Vertex *_vtx, size_t _size, const Image *_img);
            void draw(const Vertex *_vtx, size_t _size, VertexArray::Type _type);

            void clear(const Color &_clr = { 255, 255, 255, 255 });

            virtual [[nodiscard]] Point2<uint32_t> getSize() const = 0;

        protected:
            RenderTarget() = default;

            [[nodiscard]] HBITMAP getDib() const;

        private:
            void drawPixel(const Point2<uint32_t> &_pos, const Color &_clr);
            void drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec);

            HBITMAP m_dib;
            uint32_t *m_data = nullptr;
            Point2<uint32_t> m_size;
    };
}
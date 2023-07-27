#pragma once

#include  <windows.h>

#include "Engine/Rendering/Texture.hpp"
#include "Engine/Rendering/VertexArray.hpp"

namespace eng
{
    class RenderTarget
    {
        public:
            void draw(const IDrawable &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex *_vtx, size_t _size, const Texture *_txtr);
            void draw(const Vertex *_vtx, size_t _size, VertexArray::Type _type);

            virtual [[nodiscard]] Point2<uint32_t> getSize() const = 0;

            void clear(const Color &_clr = { 0, 0, 0, 255 });

        protected:
            RenderTarget() = default;

            void create(uint32_t _x, uint32_t _y);

            [[nodiscard]] uint8_t *getData() const;
            [[nodiscard]] HBITMAP getDib() const;

        private:
            void drawPixel(const Point2<uint32_t> &_pos, Color _clr);
            void drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec);
            void triRangeApply(const Vertex *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr);

            HBITMAP m_dib;
            uint8_t *m_data = nullptr;
    };
}
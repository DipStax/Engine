#ifndef ENG_ZBUFFER_HPP
#define ENG_ZBUFFER_HPP

#include <memory>
#include <vector>

#include  <windows.h>

#include "Engine/Rendering/RenderTexture.hpp"
#include "Engine/Rendering/IDrawable3D.hpp"

namespace eng
{
    class RenderTarget3D
    {
        public:
            ~RenderTarget3D() = default;

            void create(uint32_t _x, uint32_t _y);

            void draw(const IDrawable3D &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex *_vtx, const float *_depth, size_t _size, const Texture *_txtr);
            void draw(const Vertex *_vtx, size_t _size, VertexArray::Type _type);

            void clear(const Color &_clr = { 255, 255, 255, 255 });

        protected:
            RenderTarget3D() = default;

        private:
            void triRangeApply(const Vertex *_vtx, const float *_depth, int32_t _line, const Point2<uint32_t> &_range, const Texture * _txtr);

            RenderTexture m_rdTxtr;
            std::vector<float> m_depth;
    };
}

#endif
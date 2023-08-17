#ifndef ENG_REND_RENDERTARGET_HPP
#define ENG_REND_RENDERTARGET_HPP

#include <vector>
#include <Windows.h>

#include "Engine/Rendering/IDrawable3D.hpp"
#include "Engine/Rendering/VertexArray.hpp"
#include "Engine/Camera.hpp"

namespace eng
{
    class RenderTarget
    {
        public:
            void setCamera(const Camera &_cam);

            // 32 rendering
            void draw(const IDrawable &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex *_vtx, size_t _size, const Texture *_txtr);
            void draw(const Vertex *_vtx, size_t _size, VertexArray::Type _type);

            // 3d rendering
            void draw(const IDrawable3D &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex3D *_vtx, size_t _size, const Texture *_txtr);
            void draw(const Vertex3D *_vtx, size_t _size, VertexArray::Type _type);

            virtual [[nodiscard]] Point2<uint32_t> getSize() const = 0;

            void clear(const Color &_clr = { 0, 0, 0, 255 });

        protected:
            RenderTarget() = default;

            void create(uint32_t _x, uint32_t _y, const Camera &_cam = Camera());

            [[nodiscard]] uint8_t *getData() const;
            [[nodiscard]] HBITMAP getDib() const;

        private:
            void setPixel(const Point2<uint32_t> &_pos, Color _clr, float _depth = 0.f);
            void drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec);
            void triRangeApply(const Vertex *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr);
            void triRangeApply(const Vertex3D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture * _txtr);

            Camera m_cam;
            HBITMAP m_dib;
            std::vector<float> m_depth;
            uint8_t *m_data = nullptr;
    };
}

#endif
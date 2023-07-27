#ifndef ENG_ZBUFFER_HPP
#define ENG_ZBUFFER_HPP

#include <memory>
#include <vector>

#include  <windows.h>

#include "Engine/Rendering/RenderTexture.hpp"
#include "Engine/Rendering/IDrawable3D.hpp"
#include "Engine/Camera.hpp"

namespace eng
{
    class RenderTarget3D
    {
        public:
            ~RenderTarget3D() = default;

            void setCamera(float _fov, const Point2<float> &_range);
            void moveCamera(const Vector3<float> &_move);
            void rotateCamera(const Point3<float> &_rot);

            void draw(const IDrawable3D &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex3D *_vtx, size_t _size, const Texture *_txtr);

            virtual [[nodiscard]] Point2<uint32_t> getSize() const = 0;

            [[nodiscard]] Texture &&getTexture() const;

            void clear(const Color &_clr = { 0, 0, 0, 255 });

        protected:
            RenderTarget3D() = default;

            void create(uint32_t _x, uint32_t _y);

        private:
            void triRangeApply(const Vertex3D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture * _txtr);

            RenderTexture m_rdTxtr;
            std::vector<float> m_depth;
            Camera m_camera;
    };
}

#endif
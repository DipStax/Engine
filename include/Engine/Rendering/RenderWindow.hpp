#ifndef ENG_REND_RENDERWINDOW_HPP
#define ENG_REND_RENDERWINDOW_HPP

#include "Engine/Maths/Point3.hpp"
#include "Engine/Rendering/RenderTarget.hpp"
#include "Engine/Rendering/Vertex.hpp"
// #include "Engine/Rendering/ZBuffer.hpp"
#include "Engine/Camera.hpp"
#include "Engine/Window.hpp"

namespace eng
{
    class RenderWindow : public Window, public RenderTarget
    {
        public:
            RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title);
            ~RenderWindow() = default;

            [[nodiscard]] Point2<uint32_t> getSize() const;

            void setCamera(float _fov, const Point2<float> &_range);
            void moveCamera(const Vector3<float> &_move);
            void rotateCamera(const Point3<float> &_rot);

            void display() const;

        protected:
            void render(HDC _draw) const;

        private:
            // ZBuffer m_zbuffer;

            Camera m_camera;
    };
}

#endif
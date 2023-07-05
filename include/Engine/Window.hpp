#ifndef ENG_WINDOW_HPP
#define ENG_WINDOW_HPP

#include "Engine/Rendering/ZBuffer.hpp"
#include "Engine/Ressource/Model.hpp"
#include "Engine/Camera.hpp"

namespace eng
{
    class Window
    {
        public:
            Window() = default;
            Window(const Vector2<uint32_t> &_size, const std::string &_title);
            ~Window() = default;

            [[nodiscard]] bool isOpen() const;

            void setCamera(float _fov, Point2<float> _range);
            void moveCamera(Vector3<float> _move);
            void rotateCamera(Point3<float> _rot);

            [[nodiscard]] Point3<float> project(const Point3<float> &_pt);

            void drawModel(const Model &_model);
            void render();

        protected:
            static constexpr wchar_t WIN_className[]  = L"Sample Window Class";
            static constexpr WNDCLASS WIN_winClass = {
                .lpfnWndProc = WindowProc,
                .hInstance = hInstance,
                lpszClassName WIN_className
            };

        private:
            HWND m_implWin;
            bool m_open = false;

            ZBuffer m_zbuffer;

            Camera m_camera;
    };
}

#endif
#ifndef ENG_WINDOW_HPP
#define ENG_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "Engine/Rendering/ZBuffer.hpp"
#include "Engine/Ressource/Model.hpp"
#include "Engine/Camera.hpp"

namespace eng
{
    class Window : public sf::RenderWindow
    {
        public:
            Window() = default;
            Window(sf::VideoMode _vmode, const std::string &_title, uint32_t _style = sf::Style::Default,
                const sf::ContextSettings &_set = sf::ContextSettings());
            ~Window() = default;

            void setCamera(float _fov, Point2<float> _range);
            void moveCamera(Vector3<float> _move);
            void rotateCamera(Point3<float> _rot);

            [[nodiscard]] Point3<float> project(const Point3<float> &_pt);

            void drawModel(const Model &_model);
            void render();

        private:
            ZBuffer m_zbuffer;

            Camera m_camera;
    };
}

#endif
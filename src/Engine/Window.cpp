#include "Engine/Maths/Maths.hpp"
#include "Engine/Rendering/Triangle.hpp"
#include "Engine/Window.hpp"

namespace eng
{
    Window::Window(sf::VideoMode _vmode, const std::string& _title, uint32_t _style, const sf::ContextSettings& _set)
        : sf::RenderWindow(_vmode, _title, _style, _set), m_camera(), m_zbuffer({ _vmode.width, _vmode.height })
    {
    }

    void Window::setCamera(float _fov, Point2<float> _range)
    {
        m_camera.setFov(_fov);
        m_camera.setRange(_range.x, _range.y);
        m_camera.setSize(static_cast<float>(getSize().x), static_cast<float>(getSize().y));
    }

    void Window::moveCamera(Vector3<float> _move)
    {
        m_camera.move(_move);
    }

    void Window::rotateCamera(Point3<float> _rot)
    {
        _rot.x = toRad(_rot.x);
        _rot.y = toRad(_rot.y);
        _rot.z = toRad(_rot.z);
        m_camera.rotate(_rot);
    }

    Point3<float> Window::project(const Point3<float> &_pt)
    {
        return m_camera.process(_pt);
    }

    void Window::drawModel(const Model &_model)
    {
        const std::vector<Point3<float>> &txtrPt = _model.getTexturePoint();
        const std::vector<Point3<float>> &points = _model.getPoint();
        sf::Image img = _model.getTexture()->copyToImage();
        std::array<float, 3> depth;
        std::vector<Point3<float>> projection;
        Triangle triangle;

        for (const auto &_pt : points)
            projection.push_back(project(_pt));
        for (const auto &_poly : _model.getPoly()) {
            // add backface culling
            for (size_t it = 0; it < _poly.size(); it++) {
                if (_poly.at(it).x > 0)
                    triangle.pos[it] = projection[_poly.at(it).x - 1];
                else
                    triangle.pos[it] = projection[projection.size() + _poly.at(it).x];
                if (_poly.at(it).y > 0)
                    triangle.texCoords[it] = txtrPt[_poly.at(it).y - 1].as2();
                else if (_poly.at(it).y < 0)
                    triangle.texCoords[it] = txtrPt[txtrPt.size() + _poly.at(it).y].as2();
            }
            m_zbuffer.draw(triangle, img);
        }
        m_zbuffer.render();
    }

    void Window::render()
    {
        draw(m_zbuffer);
        display();
        m_zbuffer.setSize({ getSize().x, getSize().y });
    }
}
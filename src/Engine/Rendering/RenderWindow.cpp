#include "Engine/Maths/Maths.hpp"
#include "Engine/Rendering/RenderWindow.hpp"

namespace eng
{
    RenderWindow::RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title)
        : Window(_x, _y, _title)
    {
        Point2<uint32_t> size = getSize();

        create(size.y, size.x);
    }

    Point2<uint32_t> RenderWindow::getSize() const
    {
        return Window::getSize();
    }

    void RenderWindow::setCamera(float _fov, const Point2<float> &_range)
    {
        m_camera.setFov(_fov);
        m_camera.setRange(_range.x, _range.y);
        m_camera.setSize(static_cast<float>(getSize().x), static_cast<float>(getSize().y));
    }

    void RenderWindow::moveCamera(const Vector3<float> &_move)
    {
        m_camera.move(_move);
    }

    void RenderWindow::rotateCamera(const Point3<float> &_rot)
    {
        m_camera.rotate({ toRad(_rot.x), toRad(_rot.y), toRad(_rot.z) });
    }

    void RenderWindow::display() const
    {
        InvalidateRect(getWindow(), NULL, FALSE);
    }

    void RenderWindow::render(HDC _draw) const
    {
        Point2<uint32_t> size = getSize();
        HDC hdc = CreateCompatibleDC(_draw);
        HBITMAP olddib = static_cast<HBITMAP>(SelectObject(hdc, getDib()));

        BitBlt(_draw, 0, 0, size.x, size.y, hdc, 0, 0, SRCCOPY);
        SelectObject(hdc, olddib);
        DeleteDC(hdc);
    }
}
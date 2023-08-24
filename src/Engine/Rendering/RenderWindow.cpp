#include "Engine/Maths/Maths.hpp"
#include "Engine/Rendering/RenderWindow.hpp"
#include "Engine/Rendering/Sprite.hpp"

namespace eng
{
    RenderWindow::RenderWindow(uint32_t _x, uint32_t _y, const std::string &_title)
        : Window(_x, _y, _title)
    {
        Point2<uint32_t> size = getSize();
        Camera cam{};

        cam.setFov(110.f).setRange(0.1f, 100.f).setSize(static_cast<float>(size.x), static_cast<float>(size.y)).move({ 0, 0, -10 });
        create(size.y, size.x, cam);
    }

    Point2<uint32_t> RenderWindow::getSize() const
    {
        return Window::getSize();
    }

    void RenderWindow::setCamera(const Camera &_cam)
    {
        m_cam = _cam;
    }

    void RenderWindow::display()
    {
        InvalidateRect(getWindow(), NULL, FALSE);
    }

    void RenderWindow::render(HDC _draw) const
    {
        Point2<uint32_t> size = getSize();
        BITMAPINFO bmi;

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = size.x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(size.y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = getBpp();
        bmi.bmiHeader.biCompression = BI_RGB;
        SetDIBitsToDevice(_draw, 0, 0, size.x, size.y, 0, 0, 0, size.y, getData(), &bmi, DIB_RGB_COLORS);
    }
}
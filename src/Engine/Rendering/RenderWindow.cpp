#include "Engine/Maths/Maths.hpp"
#include "Engine/Rendering/RenderWindow.hpp"
#include "Engine/Rendering/Sprite.hpp"

namespace eng
{
    RenderWindow::RenderWindow(uint32_t _x, uint32_t _y, const std::string &_title)
        : Window(_x, _y, _title)
    {
        Point2<uint32_t> size = getSize();

        create(size.y, size.x);
    }

    Point2<uint32_t> RenderWindow::getSize() const
    {
        return Window::getSize();
    }

    void RenderWindow::display()
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
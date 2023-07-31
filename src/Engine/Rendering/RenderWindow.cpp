#include "Engine/Maths/Maths.hpp"
#include "Engine/Rendering/RenderWindow.hpp"
#include "Engine/Rendering/Sprite.hpp"

namespace eng
{
    RenderWindow::RenderWindow(uint32_t _x, uint32_t _y, const std::string &_title)
        : Window(_x, _y, _title)
    {
        Point2<uint32_t> size = getSize();

        RenderTarget::create(size.y, size.x);
        RenderTarget3D::create(size.y, size.x);
    }

    Point2<uint32_t> RenderWindow::getSize() const
    {
        return Window::getSize();
    }

    void RenderWindow::draw(const IDrawable &_elem, const Texture *_txtr)
    {
        RenderTarget::draw(_elem, _txtr);
    }

    void RenderWindow::draw(const IDrawable3D &_elem, const Texture *_txtr)
    {
        RenderTarget3D::draw(_elem, _txtr);
    }

    void RenderWindow::clear(const Color& _clr)
    {
        RenderTarget::clear(_clr);
        RenderTarget3D::clear(_clr);
    }

    void RenderWindow::display()
    {
        /*Sprite sprt;
        Texture txtr = getTexture();

        sprt.setTexture(txtr);
        draw(sprt);*/
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
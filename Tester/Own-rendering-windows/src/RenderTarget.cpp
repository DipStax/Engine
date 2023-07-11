#include <cmath>

#include "RenderTarget.hpp"

namespace tester
{
    void RenderTarget::create(uint32_t _x, uint32_t _y)
    {
        HDC hdc = GetDC(NULL);
        BITMAPINFO bmi;

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = getSize().x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(getSize().y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        m_dib = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&m_data), NULL, NULL);
        ReleaseDC(NULL, hdc);
    }

    void RenderTarget::clear(const Color &_clr)
    {
        std::fill(m_data, m_data + getSize().x * getSize().y, CLR(_clr));
    }

    void RenderTarget::draw(const IDrawable &_elem)
    {
        _elem.draw(*this);
    }

    HBITMAP RenderTarget::getDib() const
    {
        return m_dib;
    }

    void RenderTarget::draw(const Pixel *_pos, size_t _size, Vertex::Type _type)
    {
        if (_type == Vertex::Type::pixel) {
            for (size_t it = 0; it < _size; it++)
                drawPixel(_pos[it]);
        } else if (_type == Vertex::Type::line || _type == Vertex::Type::polygone) {
            for (size_t it = 1; it < _size; it++)
                drawLine(_pos[it - 1].pos, _pos[it].pos, _pos[it - 1].clr);
            if (_type == Vertex::Type::polygone)
                drawLine(_pos[_size - 1].pos, _pos[0].pos, _pos[_size - 1].clr);
        }
    }

    void RenderTarget::drawPixel(const Pixel &_px)
    {
        size_t pos = _px.pos.y * m_size.y + _px.pos.x;

        if (pos < getSize().x * getSize().y)
            m_data[pos] = CLR(_px.clr);
    }

    void RenderTarget::drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec, const Color &_clr)
    {
        HDC hdc = CreateCompatibleDC(NULL);
        HBITMAP olddib = (HBITMAP)SelectObject(hdc, m_dib);

        MoveToEx(hdc, _first.x, _first.y, NULL);
        LineTo(hdc, _sec.x, _sec.y);
        SelectObject(hdc, olddib);
    }
}
#include <cmath>

#include "RenderTarget.hpp"

namespace tester
{
    void RenderTarget::create(uint32_t _x, uint32_t _y)
    {
        HDC hdc = GetDC(NULL);
        BITMAPINFO bmi;

        m_size = { _x, _y };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = _x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(_y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        m_dib = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&m_data), NULL, NULL);
        ReleaseDC(NULL, hdc);
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
        } else if (_type == Vertex::Type::line) {
            for (size_t it = 1; it < _size; it++)
                drawLine(_pos[it - 1].pos, _pos[it].pos, _pos[it - 1].clr);
            if (_type == Vertex::Type::polygone)
                drawLine(_pos[_size - 1].pos, _pos[0].pos, _pos[_size - 1].clr);
        }
    }

    void RenderTarget::drawPixel(const Pixel &_px)
    {
        size_t pos = _px.pos.y * m_size.y + _px.pos.x;

        if (pos < m_size.x * m_size.y) {
            m_data[pos] = (static_cast<uint32_t>(_px.clr.B) << 16) + (static_cast<uint32_t>(_px.clr.G) << 8) + _px.clr.R;
        }
    }

    void RenderTarget::drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec, const Color &_clr)
    {
        Pixel _px = { .clr = _clr };
        const Point2<uint32_t> &left = (_first.x < _sec.x) ? _first : _sec;
        const Point2<uint32_t> &right = (_first.x < _sec.x) ? _sec : _first;
        Point2<float> pos{ static_cast<float>(left.x), static_cast<float>(left.y) };
        int32_t dx = static_cast<int32_t>(right.x) - static_cast<int32_t>(left.x);
        int32_t dy = static_cast<int32_t>(right.y) - static_cast<int32_t>(left.y);
        uint32_t step = std::abs(dx);
        Point2<float> incr;
        Pixel px{ .clr = _clr };

        if (std::abs(dx) < std::abs(dy))
            step = std::abs(dy);
        incr = Point2<float>{ static_cast<float>(dx) / step, static_cast<float>(dy) / step };
        for (uint32_t it = 0; it < step; it++) {
            pos += incr;
            px.pos = { static_cast<uint32_t>(pos.x), static_cast<uint32_t>(pos.y) };
            drawPixel(px);
        }
    }
}
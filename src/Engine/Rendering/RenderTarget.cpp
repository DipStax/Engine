#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

#include "Engine/Container/CircleList.hpp"
#include "Engine/Maths/Maths.hpp"
#include "Engine/Rendering/RenderTarget.hpp"
#include "Engine/Rendering/PolyTri.hpp"

namespace eng
{
    void RenderTarget::create(uint32_t _x, uint32_t _y)
    {
        HDC hdc = GetDC(NULL);
        BITMAPINFO bmi;

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = _x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(_y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        m_dib = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&m_data), NULL, NULL);
        ReleaseDC(NULL, hdc);
        std::cout << "[RenderTarget] create | size: " << getSize() << std::endl;
    }

    void RenderTarget::clear(const Color &_clr)
    {
        std::fill(m_data, m_data + getSize().x * getSize().y * 4, CLR(_clr));
    }

    void RenderTarget::draw(const IDrawable & _elem, const Texture *_txtr)
    {
        _elem.draw(*this, _txtr);
    }

    void RenderTarget::draw(const Vertex *_vtx, size_t _size, const Texture * _txtr)
    {
        Point2<int32_t> min;
        Point2<int32_t> max;

        if (_size > 3) {
            for (const auto &_tri : polyTri(_vtx, _size))
                draw(_tri.data(), 3, _txtr);
        } else {
            // caluclate minimal range of the drawing on y axes
            int32_t ystart = static_cast<int32_t>(std::max(std::min({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), 0.f));
            int32_t yend = static_cast<int32_t>(std::min(std::max({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), static_cast<float>(getSize().y)));

            for (; ystart < yend; ystart++)
                triRangeApply(_vtx, ystart, triRange(_vtx, ystart), _txtr);
        }
    }

    void RenderTarget::draw(const Vertex *_vtx, size_t _size, VertexArray::Type _type)
    {
        if (_type == VertexArray::Type::point) {
            for (size_t it = 0; it < _size; it++)
                drawPixel(_vtx[it].pos.as<uint32_t>(), _vtx[it].clr);
        } else if (_type == VertexArray::Type::line || _type == VertexArray::Type::polygone) {
            for (size_t it = 1; it < _size; it++)
                drawLine(_vtx[it - 1].pos.as<uint32_t>(), _vtx[it].pos.as<uint32_t>());
            if (_type == VertexArray::Type::polygone)
                drawLine(_vtx[_size - 1].pos.as<uint32_t>(), _vtx[0].pos.as<uint32_t>());
        }
    }

    uint8_t *RenderTarget::getData() const
    {
        return m_data;
    }

    HBITMAP RenderTarget::getDib() const
    {
        return m_dib;
    }

    void RenderTarget::drawPixel(const Point2<uint32_t> &_pos, Color _clr)
    {
        HDC hdc = CreateCompatibleDC(NULL);
        HBITMAP olddib = (HBITMAP)SelectObject(hdc, m_dib);

        SetPixel(hdc, _pos.x, _pos.y, CLR(_clr));
        SelectObject(hdc, olddib);
        DeleteDC(hdc);
    }

    void RenderTarget::drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec)
    {
        HDC hdc = CreateCompatibleDC(NULL);
        HBITMAP olddib = (HBITMAP)SelectObject(hdc, m_dib);

        MoveToEx(hdc, _first.x, _first.y, NULL);
        LineTo(hdc, _sec.x, _sec.y);
        SelectObject(hdc, olddib);
        DeleteDC(hdc);
    }

    void RenderTarget::triRangeApply(const Vertex *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture * _txtr)
    {
        Point2<float> pos;
        float abc = area(_vtx[0].pos, _vtx[1].pos, _vtx[2].pos);
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;
        Point2<uint32_t> size = getSize() - 1;

        // caluclate minimal range of the drawing on x axes
        float xstart = static_cast<float>(std::max(_range.x, 0U));
        float xend = static_cast<float>(std::min(_range.y, size.x));
        for (Point2<float> px = { xstart, static_cast<float>(_line) }; px.x <= xend; px.x++) {
            // calculating mapping of the texture
            ratio1 = area(_vtx[2].pos, _vtx[0].pos, px) / abc;
            ratio2 = area(_vtx[0].pos, _vtx[1].pos, px) / abc;
            ratio3 = 1 - ratio1 - ratio2;
            pos = _vtx[1].txtrPos * ratio1 + _vtx[2].txtrPos * ratio2 + _vtx[0].txtrPos * ratio3;
            // px position is assured by calculation the minimal range in x and y axes;
            drawPixel(px.as<uint32_t>(), _txtr->getPixel(pos.as<uint32_t>()));
        }
    }
}
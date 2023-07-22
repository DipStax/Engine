#include <algorithm>
#include <array>
#include <cmath>

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
    }

    void RenderTarget::clear(const Color &_clr)
    {
        std::fill(m_data, m_data + getSize().x * getSize().y * 4, CLR(_clr));
    }

    void RenderTarget::draw(const IDrawable & _elem, const Image *_img)
    {
        _elem.draw(*this, _img);
    }

    void RenderTarget::draw(const Vertex *_vtx, size_t _size, const Image *_img)
    {
        Point2<int32_t> min;
        Point2<int32_t> max;

        if (_size > 3) {
            for (const auto &_tri : polyTri(_vtx, _size))
                draw(_tri.data(), 3, _img);
        } else {
            min = Point2<float>(std::min({ _vtx[0].pos.x, _vtx[1].pos.x, _vtx[2].pos.x }), std::min({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y })).as<int32_t>();
            max = Point2<float>(std::max({ _vtx[0].pos.x, _vtx[1].pos.x, _vtx[2].pos.x }), std::max({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y })).as<int32_t>();

            for (int32_t it = min.y; it < max.y; it++)
                triRangeApply(_vtx, it, triRange(_vtx, it), _img);
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

    void RenderTarget::triRangeApply(const Vertex *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Image *_img)
    {
        Point2<float> pos;
        float abc = area(_vtx[0].pos, _vtx[1].pos, _vtx[2].pos);
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;

        for (Point2<float> px = { static_cast<float>(_range.x), static_cast<float>(_line) }; px.x <= static_cast<float>(_range.y); px.x++) {
            ratio1 = area(_vtx[2].pos, _vtx[0].pos, px) / abc;
            ratio2 = area(_vtx[0].pos, _vtx[1].pos, px) / abc;
            ratio3 = 1 - ratio1 - ratio2;
            pos = _vtx[1].txtrPos * ratio1 + _vtx[2].txtrPos * ratio2 + _vtx[0].txtrPos * ratio3;
            drawPixel(px.as<uint32_t>(), _img->getPixel(pos.as<uint32_t>()));
        }
    }
}
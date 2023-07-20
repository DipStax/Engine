#include <cmath>

#include "CircleList.hpp"
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

    void RenderTarget::draw(const IDrawable & _elem, const Image *_img)
    {
        _elem.draw(*this, _img);
    }

    void RenderTarget::draw(const Vertex *_vtx, size_t _size, const Image *_img)
    {
        CircleList<Vertex> cl;

        for (size_t it = 0; it < _size; it++)
            cl.push_back(_vtx[it]); // memory optimisation (copying data)
    }

    void RenderTarget::draw(const Vertex *_vtx, size_t _size, VertexArray::Type _type)
    {
        if (_type == VertexArray::Type::point) {
            for (size_t it = 0; it < _size; it++)
                drawLine(_vtx[it].pos, _vtx[it].pos);
        } else if (_type == VertexArray::Type::line || _type == VertexArray::Type::polygone) {
            for (size_t it = 1; it < _size; it++)
                drawLine(_vtx[it - 1].pos, _vtx[it].pos);
            if (_type == VertexArray::Type::polygone)
                drawLine(_vtx[_size - 1].pos, _vtx[0].pos);
        }
    }

    HBITMAP RenderTarget::getDib() const
    {
        return m_dib;
    }

    void RenderTarget::drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec)
    {
        HDC hdc = CreateCompatibleDC(NULL);
        HBITMAP olddib = (HBITMAP)SelectObject(hdc, m_dib);

        MoveToEx(hdc, _first.x, _first.y, NULL);
        LineTo(hdc, _sec.x, _sec.y);
        SelectObject(hdc, olddib);
    }
}
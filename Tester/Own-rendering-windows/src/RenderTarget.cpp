#include <iostream>
#include <algorithm>
#include <array>
#include <cmath>

#include "Engine/Area.hpp"
#include "CircleList.hpp"
#include "RenderTarget.hpp"
#include "PolyTri.hpp"

namespace tester
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
        std::fill(m_data, m_data + getSize().x * getSize().y, CLR(_clr));
    }

    void RenderTarget::draw(const IDrawable & _elem, const Image *_img)
    {
        _elem.draw(*this, _img);
    }

    Point2<uint32_t> triRange(const Vertex *_vtx, int32_t _line)
    {
        Point2<float> res;
        bool first = false;
        float clres = 0;

        for (size_t it = 0; it < 3; it++) {
            if (_vtx[it].pos.y == _line && _line == _vtx[it + 1].pos.y) {
                res = { std::min(_vtx[it].pos.x, _vtx[(it + 1) % 3].pos.x), std::max(_vtx[it].pos.x, _vtx[(it + 1) % 3].pos.x) };
                break;
            } else if ((_vtx[it].pos.y <= _line && _line <= _vtx[(it + 1) % 3].pos.y) ||
                (_vtx[(it + 1) % 3].pos.y <= _line && _line <= _vtx[it].pos.y)) {
                clres = _vtx[it].pos.x;

                if (_vtx[(it + 1) % 3].pos.x != _vtx[it].pos.x) {
                    float slope = (_vtx[(it + 1) % 3].pos.y - _vtx[it].pos.y) / (_vtx[(it + 1) % 3].pos.x - _vtx[it].pos.x);
                    clres = (static_cast<float>(_line) - (_vtx[it].pos.y - slope * _vtx[it].pos.x)) / slope;
                }
                if (!first) {
                    res.x = clres;
                    first = true;
                } else {
                    res.y = clres;
                }
            }
        }
        if (res.x > res.y)
            std::swap(res.x, res.y);
        return res.as<uint32_t>();
    }

    void RenderTarget::draw(const Vertex *_vtx, size_t _size, const Image *_img)
    {
        std::vector<std::array<Vertex, 3>> ltri;
        Point2<int32_t> min;
        Point2<int32_t> max;

        if (_size > 3) {
            ltri = polyTri(_vtx, _size);
            for (auto &_tri : ltri)
                draw(_tri.data(), 3, _img);
        } else {
            min = Point2<float>(std::min({ _vtx[0].pos.x, _vtx[1].pos.x, _vtx[2].pos.x }), std::min({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y })).as<int32_t>();
            max = Point2<float>(std::max({ _vtx[0].pos.x, _vtx[1].pos.x, _vtx[2].pos.x }), std::max({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y })).as<int32_t>();

            for (int32_t it = min.y; it < max.y; it++)
                triRangeApply(_vtx, it, triRange(_vtx, it), _img);
        }
    }


    // void RenderTarget::scanline(const CircleList<Vertex> &_cl, const Image &_img, size_t _line)
    // {
        // using CrossArray =  std::vector<std::pair<float, size_t>>;
        // using ClCrossArray =  std::vector<std::pair<float, size_t>>;

        // auto crossPoint = [] (const Point2<float> &_pt1, const Point2<float> &_pt2, size_t _line) {
        //     if ((_line < _pt1.y && _line < _pt2.y) || (_pt1.y < _line && _pt2.y < _line))
        //         return std::numeric_limits<float>::quiet_NaN();
        //     if (_pt1.y == _pt2.y)
        //         return _pt1.x;
        //     float x = _pt1.x + (_line - _pt1.y) * (_pt2.x - _pt1.x) / (_pt2.y - _pt1.y);
        //     if ((x < _pt1.x && x < _pt2.x) || (_pt1.x < x && _pt2.x < x))
        //         return std::numeric_limits<float>::quiet_NaN();
        //     return x;
        // };
        // CrossArray ca;
        // ClCrossArray clca;

        // std::cout << "---------- [Scanline] scaning new line: " << _line << " ----------" << std::endl;
        // for (size_t it = 0; it < _cl.size(); it++) {
        //     // vvvvv dont recacluate the prime of _a vertex
        //     Point2<float> pos = _cl[it + 1].pos - _cl[it].pos;
        //     pos = _cl[it + 1].pos - pos / std::sqrt(std::pow(pos.x, 2) + std::pow(pos.y, 2));
        //     // ^^^^^
        //     // std::cout << "Vertex calculated: " << _cl[it].pos << " to " << pos << std::endl;
        //     float crossX = crossPoint(_cl[it].pos, pos, _line);
        //     // std::cout << "Line cross at: x=" << crossPoint(_cl[it].pos, pos, _line) << std::endl;
        //     if (crossX != std::isnan(crossX))
        //         ca.emplace_back(crossX, it);
        // }
        // std::sort(ca.begin(), ca.end(), [] (const std::pair<float, size_t> &_left, const std::pair<float, size_t> &_right) {
        //     return _left.first < _right.first;
        // });
        // for (size_t it = 0; it < ca.size(); it++)
        //     clca.push_back(ca[it]);
        // for (size_t it = 0; it < ca.size(); it += 2)
        //     processRange(_cl, clca[it], clca[it + 1], _line, _img);
    // }


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
            pos = _vtx[0].txtrPos * ratio1 + _vtx[1].txtrPos * ratio2 + _vtx[2].txtrPos * ratio3;
            drawPixel(px.as<uint32_t>(), _img->getPixel(pos.as<uint32_t>()));
        }
    }
}
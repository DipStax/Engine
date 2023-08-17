#include <algorithm>
#include <iostream>

#include "Engine/Rendering/RenderTarget.hpp"
#include "Engine/Maths/Maths.hpp"
#include "Engine/Rendering/PolyTri.hpp"

namespace eng
{
    /*******************************
     * PUBLIC
    ********************************/

    void RenderTarget::setCamera(const Camera &_cam)
    {
        m_cam = _cam;
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
                setPixel(_vtx[it].pos.as<uint32_t>(), _vtx[it].clr);
        } else if (_type == VertexArray::Type::line || _type == VertexArray::Type::polygone) {
            for (size_t it = 1; it < _size; it++)
                drawLine(_vtx[it - 1].pos.as<uint32_t>(), _vtx[it].pos.as<uint32_t>());
            if (_type == VertexArray::Type::polygone)
                drawLine(_vtx[_size - 1].pos.as<uint32_t>(), _vtx[0].pos.as<uint32_t>());
        }
    }

    void RenderTarget::draw(const IDrawable3D &_elem, const Texture *_txtr)
    {
        _elem.draw(*this, _txtr);
    }

    void RenderTarget::draw(const Vertex3D *_vtx, size_t _size, const Texture *_txtr)
    {
        // warning size isn't used because checked before using it from RenderTarget
        // but function is public so undefined behavior
        std::ignore = _size;
        std::vector<Vertex3D> vtx(_vtx, _vtx + _size);

        for (auto &_mvtx : vtx)
            _mvtx.pos = m_cam.project(_mvtx.pos);
        // caluclate minimal range of the drawing on y axes
        int32_t ystart = static_cast<int32_t>(std::max(std::min({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), 0.f));
        int32_t yend = static_cast<int32_t>(std::min(std::max({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), static_cast<float>(getSize().y)));

        for (; ystart < yend; ystart++)
            triRangeApply(vtx.data(), ystart, triRange(vtx.data(), ystart), _txtr);
    }

    void RenderTarget::clear(const Color &_clr)
    {
        uint32_t clr = CLR(_clr);
        size_t size = getSize().x * getSize().y * 4; // change bpp

        std::cout << "clear size: " << size << " for: " << getSize() << std::endl;
        for (size_t it = 0; it < size; it += sizeof(uint32_t))
            std::memcpy(m_data + it, &clr, sizeof(uint32_t));
        std::fill(m_depth.begin(), m_depth.end(), std::numeric_limits<float>::lowest());
    }

    /*******************************
     * PROTECTED
    ********************************/

    void RenderTarget::create(uint32_t _x, uint32_t _y, const Camera &_cam)
    {
        HDC hdc = GetDC(NULL);
        BITMAPINFO bmi;

        m_cam = _cam;
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = _x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(_y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        m_dib = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&m_data), NULL, NULL);
        ReleaseDC(NULL, hdc);
        std::cout << "[RenderTarget] create | size: " << getSize() << std::endl;
        m_depth.resize(_x * _y, std::numeric_limits<float>::lowest());
    }

    uint8_t *RenderTarget::getData() const
    {
        return m_data;
    }

    HBITMAP RenderTarget::getDib() const
    {
        return m_dib;
    }

    /*******************************
     * PRIVATE
    ********************************/

    void RenderTarget::setPixel(const Point2<uint32_t> &_pos, Color _clr, float _depth)
    {
        // handling of alpha
        uint32_t pos = _pos.y * getSize().x + _pos.x;
        uint32_t clr = CLR(_clr);
        uint32_t rclr = CLR(_clr);

        if (m_depth[pos] <= _depth)
            for (size_t it = 0; it < sizeof(uint32_t); it++) {
                rclr |= ((clr >> it) & 1) << (sizeof(uint32_t) - 1 - it);
            m_depth[pos] = _depth;
            std::memcpy(m_data + pos, &rclr, sizeof(uint32_t)); // add bpp to the copy to
        }
    }

    void RenderTarget::drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec)
    {
        // doesn't manage the depth
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
            setPixel(px.as<uint32_t>(), _txtr->getPixel(pos.as<uint32_t>()));
        }
    }

    void RenderTarget::triRangeApply(const Vertex3D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr)
    {
        // check the use of https://learn.microsoft.com/fr-fr/windows/win32/api/wingdi/nf-wingdi-setdibitstodevice
        Point2<float> rpos;
        uint32_t arrPos = 0;
        float abc = area(_vtx[0].pos.as2(), _vtx[1].pos.as2(), _vtx[2].pos.as2());
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;
        float depth = 0;
        // caluclate minimal range of the drawing on x axes
        float xstart = static_cast<float>(std::max(_range.x, 0U));
        float xend = static_cast<float>(std::min(_range.y, getSize().x));

        arrPos = _line * getSize().x + static_cast<uint32_t>(xstart);
        for (Point2<float> pos = { xstart, static_cast<float>(_line) }; pos.x <= xend; pos.x++, arrPos++) {
            // calculating mapping of the depth
            ratio1 = area(_vtx[2].pos.as2(), _vtx[0].pos.as2(), pos) / abc;
            ratio2 = area(_vtx[0].pos.as2(), _vtx[1].pos.as2(), pos) / abc;
            ratio3 = 1 - ratio1 - ratio2;
            depth = _vtx[1].pos.z * ratio1 + _vtx[2].pos.z * ratio2 + _vtx[0].pos.z * ratio3;
            // check the depth on the pixel
            if (depth > m_depth[arrPos]) {
                // calculating mapping of the texture
                rpos = _vtx[1].txtrPos * ratio1 + _vtx[2].txtrPos * ratio2 + _vtx[0].txtrPos * ratio3;
                setPixel(rpos.as<uint32_t>(), _txtr->getPixel(pos.as<uint32_t>()), depth); // double checking m_depth
            }
        }
    }
}
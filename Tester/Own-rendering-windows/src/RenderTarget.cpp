#include "RenderTarget.hpp"

namespace tester
{
    void RenderTarget::draw(const IDrawable &_elem)
    {
        _elem.draw(*this);
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
        m_renderData[_px.pos.y * getSize().y + _px.pos.x] = _px.clr;
    }

    void RenderTarget::drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec, const Color &_clr)
    {
        // https://classic.csunplugged.org/documents/activities/community-activities/line-drawing/line-drawing.pdf
        Pixel _px = { .clr = _clr };
        const Point2<uint32_t> &left = (_first.x < _sec.x) ? _first : _sec;
        const Point2<uint32_t> &right = (_first.x < _sec.x) ? _sec : _first;
        uint32_t dx = right.x - left.x;
        uint32_t dy = right.y - left.y;
        uint32_t d = 2 * dy - dx;
        uint32_t y = left.y;

        for (uint32_t x = left.x; x < right.x; x++) {
            _px.pos = { x, y };
            drawPixel(_px);
            if (d > 0) {
                y++;
                d -= 2 * dx;
            }
            d *= 2 * dy;
        }
    }
}
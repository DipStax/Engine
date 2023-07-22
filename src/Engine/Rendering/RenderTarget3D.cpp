#include <algorithm>
#include <limits>

#include "Engine/Maths/Maths.hpp"
#include "Engine/Rendering/RenderTarget3D.hpp"
#include "Engine/Rendering/PolyTri.hpp"

namespace eng
{
    void RenderTarget3D::create(uint32_t _x, uint32_t _y)
    {
        m_rdTxtr.create(_x, _y);
        m_depth.resize(_x * _y, -std::numeric_limits<float>::max());
    }

    void RenderTarget3D::draw(const IDrawable3D &_elem, const Texture *_txtr)
    {
        _elem.draw(*this, _txtr);
    }

    void RenderTarget3D::draw(const Vertex *_vtx, const float *_depth, size_t _size, const Texture *_txtr)
    {
        std::ignore = _size;
        // checking if the size is 3 or use polyTri function with depth assigned
        Point2<int32_t> min = Point2<float>(std::min({ _vtx[0].pos.x, _vtx[1].pos.x, _vtx[2].pos.x }), std::min({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y })).as<int32_t>();
        Point2<int32_t> max = Point2<float>(std::max({ _vtx[0].pos.x, _vtx[1].pos.x, _vtx[2].pos.x }), std::max({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y })).as<int32_t>();

        for (int32_t it = min.y; it < max.y; it++)
            triRangeApply(_vtx, _depth, it, triRange(_vtx, it), _txtr);
    }

    void RenderTarget3D::draw(const Vertex *_vtx, size_t _size, VertexArray::Type _type)
    {
        m_rdTxtr.draw(_vtx, _size, _type);
    }

    void RenderTarget3D::clear(const Color &_clr)
    {
        m_rdTxtr.clear(_clr);
        std::fill(m_depth.begin(), m_depth.end(), -std::numeric_limits<float>::max());
    }

    void RenderTarget3D::triRangeApply(const Vertex *_vtx, const float *_depth, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr)
    {
        Point2<float> pos;
        Vertex vtx = { .pos = { static_cast<float>(_range.x), static_cast<float>(_line) } };
        float abc = area(_vtx[0].pos, _vtx[1].pos, _vtx[2].pos);
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;

        for (; vtx.pos.x <= static_cast<float>(_range.y); vtx.pos.x++) {
            // calculate depth
            ratio1 = area(_vtx[2].pos, _vtx[0].pos, vtx.pos) / abc;
            ratio2 = area(_vtx[0].pos, _vtx[1].pos, vtx.pos) / abc;
            ratio3 = 1 - ratio1 - ratio2;
            pos = _vtx[1].txtrPos * ratio1 + _vtx[2].txtrPos * ratio2 + _vtx[0].txtrPos * ratio3;
            vtx.clr = _txtr->getPixel(pos.as<uint32_t>());
            m_rdTxtr.draw(&vtx, 1, VertexArray::Type::point);
        }
    }
}
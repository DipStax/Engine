#include <algorithm>
#include <limits>
#include <vector>

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

    void RenderTarget3D::setCamera(float _fov, const Point2<float> &_range)
    {
        m_camera.setFov(_fov);
        m_camera.setRange(_range.x, _range.y);
        m_camera.setSize(static_cast<float>(getSize().x), static_cast<float>(getSize().y));
    }

    void RenderTarget3D::moveCamera(const Vector3<float> &_move)
    {
        m_camera.move(_move);
    }

    void RenderTarget3D::rotateCamera(const Point3<float> &_rot)
    {
        m_camera.rotate({ toRad(_rot.x), toRad(_rot.y), toRad(_rot.z) });
    }

    void RenderTarget3D::draw(const IDrawable3D &_elem, const Texture *_txtr)
    {
        _elem.draw(*this, _txtr);
    }

    void RenderTarget3D::draw(const Vertex3D *_vtx, size_t _size, const Texture *_txtr)
    {
        std::ignore = _size;
        std::vector<Vertex3D> vtx(_vtx, _vtx + _size);

        for (auto &_mvtx : vtx)
            _mvtx.pos = m_camera.project(_mvtx.pos);
        // checking if the size is 3 or use polyTri function with depth assigned
        Point2<int32_t> min = Point2<float>(std::min({ vtx[0].pos.x, vtx[1].pos.x, vtx[2].pos.x }), std::min({ vtx[0].pos.y, vtx[1].pos.y, vtx[2].pos.y })).as<int32_t>();
        Point2<int32_t> max = Point2<float>(std::max({ vtx[0].pos.x, vtx[1].pos.x, vtx[2].pos.x }), std::max({ vtx[0].pos.y, vtx[1].pos.y, vtx[2].pos.y })).as<int32_t>();

        for (int32_t it = min.y; it < max.y; it++)
            triRangeApply(vtx.data(), it, triRange(vtx.data(), it), _txtr);
    }

    Texture &&RenderTarget3D::getTexture() const
    {
        return std::move(m_rdTxtr.getTexture());
    }

    void RenderTarget3D::clear(const Color &_clr)
    {
        m_rdTxtr.clear(_clr);
        std::fill(m_depth.begin(), m_depth.end(), -std::numeric_limits<float>::max());
    }

    void RenderTarget3D::triRangeApply(const Vertex3D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr)
    {
        Point2<float> pos;
        Vertex vtx = { .pos = { static_cast<float>(_range.x), static_cast<float>(_line) } };
        float abc = area(_vtx[0].pos.as2(), _vtx[1].pos.as2(), _vtx[2].pos.as2());
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;
        float depth = 0;

        //std::cout << "Range draw: " << _range << std::endl;
        for (; vtx.pos.x <= static_cast<float>(_range.y); vtx.pos.x++) {
            // calculate depth
            ratio1 = area(_vtx[2].pos.as2(), _vtx[0].pos.as2(), vtx.pos) / abc;
            ratio2 = area(_vtx[0].pos.as2(), _vtx[1].pos.as2(), vtx.pos) / abc;
            ratio3 = 1 - ratio1 - ratio2;
            depth = _vtx[1].pos.z * ratio1 + _vtx[2].pos.z * ratio2 + _vtx[0].pos.z * ratio3;
            //std::cout << "Depth calculated for " << vtx.pos << ": " << depth << std::endl;
            //std::cout << "\tDepth at this pos: " << m_depth[vtx.pos.as<uint32_t>().y * getSize().x + vtx.pos.as<uint32_t>().x] << std::endl;
            if (depth > m_depth[vtx.pos.as<uint32_t>().y * getSize().x + vtx.pos.as<uint32_t>().x]) {
                pos = _vtx[1].txtrPos * ratio1 + _vtx[2].txtrPos * ratio2 + _vtx[0].txtrPos * ratio3;
                vtx.clr = _txtr->getPixel(pos.as<uint32_t>());
                m_depth[vtx.pos.as<uint32_t>().y * getSize().x + vtx.pos.as<uint32_t>().x] = depth;
                m_rdTxtr.draw(&vtx, 1, VertexArray::Type::point);
            }
        }
    }
}
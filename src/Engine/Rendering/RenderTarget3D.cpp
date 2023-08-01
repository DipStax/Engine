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
        // caluclate minimal range of the drawing on y axes
        int32_t ystart = static_cast<int32_t>(std::max(std::min({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), 0.f));
        int32_t yend = static_cast<int32_t>(std::min(std::max({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), static_cast<float>(getSize().y)));

        for (; ystart < yend; ystart++)
            triRangeApply(vtx.data(), ystart, triRange(vtx.data(), ystart), _txtr);
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
        // check the use of https://learn.microsoft.com/fr-fr/windows/win32/api/wingdi/nf-wingdi-setdibitstodevice
        Point2<float> pos;
        float abc = area(_vtx[0].pos.as2(), _vtx[1].pos.as2(), _vtx[2].pos.as2());
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;
        float depth = 0;

        // caluclate minimal range of the drawing on x axes
        float xstart = static_cast<float>(std::max(_range.x, 0U));
        float xend = static_cast<float>(std::min(_range.y, getSize().x));
        for (Vertex vtx = { { xstart, static_cast<float>(_line) } }; vtx.pos.x <= xend; vtx.pos.x++) {
            // calculating mapping of the depth
            ratio1 = area(_vtx[2].pos.as2(), _vtx[0].pos.as2(), vtx.pos) / abc;
            ratio2 = area(_vtx[0].pos.as2(), _vtx[1].pos.as2(), vtx.pos) / abc;
            ratio3 = 1 - ratio1 - ratio2;
            depth = _vtx[1].pos.z * ratio1 + _vtx[2].pos.z * ratio2 + _vtx[0].pos.z * ratio3;
            // check the depth on the pixel
            if (depth > m_depth[vtx.pos.as<uint32_t>().y * getSize().x + vtx.pos.as<uint32_t>().x]) {
                // calculating mapping of the texture
                pos = _vtx[1].txtrPos * ratio1 + _vtx[2].txtrPos * ratio2 + _vtx[0].txtrPos * ratio3;
                vtx.clr = _txtr->getPixel(pos.as<uint32_t>());
                // set depth and color
                m_depth[vtx.pos.as<uint32_t>().y * getSize().x + vtx.pos.as<uint32_t>().x] = depth;
                m_rdTxtr.draw(&vtx, 1, VertexArray::Type::point);
            }
        }
    }
}
#include <cmath>
#include <iostream>
#include "Engine/Maths/Maths.hpp"

#include "Engine/Rendering/ZBuffer.hpp"

namespace eng
{
    ZBuffer::ZBuffer(Vector2<uint32_t> _size)
        : m_size(_size)
    {
        setSize(m_size);
    }

    void ZBuffer::clear()
    {
        std::fill(m_depth.begin(), m_depth.end(), std::numeric_limits<float>::min());
        std::fill(m_color.begin(), m_color.end(), sf::Color::Transparent);
    }

    void ZBuffer::setSize(Vector2<uint32_t> _size)
    {
        m_size = _size;
        m_depth.resize(m_size.x * m_size.y);
        m_color.resize(m_size.x * m_size.y);
        m_txtr.create(m_size.x, m_size.y);
        clear();
    }

    const Vector2<uint32_t> &ZBuffer::getSize() const
    {
        return m_size;
    }


    void ZBuffer::draw(const Triangle &_tri, const sf::Image &_img)
    {
        Point2<float> bmax = { std::min((float)m_size.x, std::max({ _tri.pos[0].x, _tri.pos[1].x, _tri.pos[2].x })), std::min((float)m_size.y, std::max({ _tri.pos[0].y, _tri.pos[1].y, _tri.pos[2].y })) };
        Point2<float> bmin = { std::max(0.f, std::min({ _tri.pos[0].x, _tri.pos[1].x, _tri.pos[2].x })), std::max(0.f, std::min({ _tri.pos[0].y, _tri.pos[1].y, _tri.pos[2].y })) };
        float total = area(_tri.pos[0].as2(), _tri.pos[1].as2(), _tri.pos[2].as2());
        float tri = 0;

        for (float y = std::floor(bmin.y); y < std::ceil(bmax.y); y++) {
            for (float x = std::floor(bmin.x); x <= std::ceil(bmax.x); x++) {
                Point3<float> pt = { x, y, 0 };

                tri = area(pt.as2(), _tri.pos[1].as2(), _tri.pos[2].as2()) + area(_tri.pos[0].as2(), pt.as2(), _tri.pos[2].as2()) + area(_tri.pos[0].as2(), _tri.pos[1].as2(), pt.as2());
                if (total - 1 <= tri && tri <= total + 1) {
                    Vector3<float> ratio = getPointRatio(_tri, pt);

                    draw(Point2<uint32_t>{ static_cast<uint32_t>(x), static_cast<uint32_t>(y) }, getDepth(_tri, ratio), getPixel(_tri, ratio, _img));
                }
            }
        }
    }

    void ZBuffer::draw(Point2<uint32_t> _pt, float _depth, Color _clr)
    {
        size_t didx = _pt.y * m_size.x + _pt.x;

        if (m_depth[didx] <  _depth) {
            m_depth[didx] = _depth;
            m_color.at(_pt.y * m_size.x + _pt.x) = _clr;
        }
    }

    void ZBuffer::render()
    {
        m_txtr.update(reinterpret_cast<const uint8_t*>(m_color.data()), m_size.x, m_size.y, 0, 0);
        m_sprite.setTexture(m_txtr);
    }

    void ZBuffer::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
    {
        _target.draw(m_sprite, _states);
    }

    Vector3<float> ZBuffe::getPointRatio(const Triangle &_tri, const Point2<float> &_pt)
    {
        float abc = area(_tri.pos[0].as2(), _tri.pos[1].as2(), _tri.pos[2].as2());
        Vector3<float> ratio;

        ratio.x = area(_tri.pos[2].as2(), _tri.pos[0].as2(), _pos) / abc;
        ratio.y = area(_tri.pos[0].as2(), _tri.pos[1].as2(), _pos) / abc;
        ratio.z = 1 - ratio.x - ratio.y;
        return ratio;
    }

    Color ZBuffer::getPixel(const Triangle &_tri, const Vector3<float> &_ratio, const sf::Image &_img)
    {
        std::array<Vector2<float>, 3> realSizeTxtr = {
            Vector2<float>{ static_cast<float>(_img.getSize().x) * _tri.texCoords[0].x, static_cast<float>(_img.getSize().y) * _tri.texCoords[0].y },
            Vector2<float>{ static_cast<float>(_img.getSize().x) * _tri.texCoords[1].x, static_cast<float>(_img.getSize().y) * _tri.texCoords[1].y },
            Vector2<float>{ static_cast<float>(_img.getSize().x) * _tri.texCoords[2].x, static_cast<float>(_img.getSize().y) * _tri.texCoords[2].y }
        };
        Vector2<float> pos = realSizeTxtr[0] * _ratio.x + realSizeTxtr[1] * _ratio.y + realSizeTxtr[2] * _ratio.z;
        return _img.getPixel(pos.x, pos.y);
    }

    // to fix
    float ZBuffer::getDepth(const Triangle &_tri, const Vector3<float> &_ratio)
    {
        return _tri.pos[0].z * _ratio.x + _tri.pos[1].z * _ratio.y + _tri.pos[2].z * _ratio.z;
    }
}
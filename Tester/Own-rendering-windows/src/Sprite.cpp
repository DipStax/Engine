#include "Sprite.hpp"
#include "RenderTarget.hpp"

namespace tester
{
    void Sprite::setImage(Image &_img)
    {
        m_img = _img;
        m_rect.pos = { 0, 0 };
        m_rect.size = _img.getSize();
    }

    void Sprite::setPosition(uint32_t _x, uint32_t _y)
    {
        setPosition({ _x, _y });
    }

    void Sprite::setPosition(const Point2<uint32_t> &_pos)
    {
        m_pos = _pos;
    }

    Point2<uint32_t> Sprite::getPosition() const
    {
        return m_pos;
    }

    void Sprite::setScale(uint32_t _rh, uint32_t _rw)
    {
        setScale({ _rh, _rw });
    }

    void Sprite::setScale(const Point2<uint32_t> &_scale)
    {
        m_scale = _scale;
    }

    Point2<uint32_t> Sprite::getScale() const
    {
        return m_scale;
    }

    void Sprite::setImgRect(Rect &_rect)
    {
        m_rect = _rect;
    }

    Rect Sprite::getImgRect() const
    {
        return m_rect;
    }

    void Sprite::draw(RenderTarget &_target, Image *_img) const
    {
        _target.draw(m_vertex, _img);
    }

    void Sprite::generateVertex()
    {
        Point2<uint32_t> size = m_img.getSize();

        m_vertex.clear();
        m_vertex.append({ m_pos, m_rect.pos });
        m_vertex.append({ { m_pos.x + size.x, m_pos.y }, { m_rect.pos.x + size.x, m_rect.pos.y  } });
        m_vertex.append({ m_pos + size, m_rect.pos + size });
        m_vertex.append({ { m_pos.x, m_pos.y + size.y }, { m_rect.pos.x, m_rect.pos.y + size.y  } });
    }
}
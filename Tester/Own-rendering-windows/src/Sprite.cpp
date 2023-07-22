#include "Sprite.hpp"
#include "RenderTarget.hpp"

namespace tester
{
    void Sprite::setImage(Image &_img)
    {
        m_img = _img;
        processRect();
    }

    void Sprite::setPosition(float _x, float _y)
    {
        setPosition({ _x, _y });
    }

    void Sprite::setPosition(const Point2<float> &_pos)
    {
        m_pos = _pos;
        processRect();
    }

    Point2<float> Sprite::getPosition() const
    {
        return m_pos;
    }

    void Sprite::setScale(float _rh, float _rw)
    {
        setScale({ _rh, _rw });
    }

    void Sprite::setScale(const Point2<float> &_scale)
    {
        m_scale = _scale;
        processRect();
    }

    Point2<float> Sprite::getScale() const
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

    void Sprite::draw(RenderTarget &_target, const Image *_img) const
    {
        _target.draw(m_vertex, &m_img);
    }

    void Sprite::processRect()
    {
        Point2<float> size = m_img.getSize().as<float>();

        m_rect = { m_pos, size * m_scale };
        m_vertex.clear();
        m_vertex.append({ m_rect.pos, { 0, 0 } });
        m_vertex.append({ { m_rect.pos.x + m_rect.size.x, m_rect.pos.y }, { size.x, 0 } });
        m_vertex.append({ m_rect.pos + m_rect.size.x, size });
        m_vertex.append({ { m_rect.pos.x, m_rect.pos.y + m_rect.size.y }, { 0, size.y } });
    }
}
#include "Engine/Rendering/Sprite.hpp"
#include "Engine/Rendering/RenderTarget.hpp"

namespace eng
{
    void Sprite::setTexture(Texture &_img)
    {

        m_txtr = _img;

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

    void Sprite::setTxtrRect(Rect _rect)
    {
        Point2<float> size = m_txtr.getSize().as<float>();

        m_rect = _rect;
        m_vertex.clear();
        m_vertex.append({ m_rect.pos, { 0, 0 } });
        m_vertex.append({ { m_rect.pos.x + m_rect.size.x - 1, m_rect.pos.y }, { size.x, 0 } });
        m_vertex.append({ m_rect.pos + m_rect.size - 1, size });
        m_vertex.append({ { m_rect.pos.x, m_rect.pos.y + m_rect.size.y - 1}, { 0, size.y } });
    }

    Rect Sprite::getTxtrRect() const
    {
        return m_rect;
    }

    void Sprite::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        std::ignore = _txtr;

        _target.draw(m_vertex, &m_txtr);
    }

    void Sprite::processRect()
    {
        Point2<float> size = m_txtr.getSize().as<float>();

        m_rect = { m_pos, size * m_scale };
        m_vertex.clear();
        m_vertex.append({ m_rect.pos, { 0, 0 } });
        m_vertex.append({ { m_rect.pos.x + m_rect.size.x - 1, m_rect.pos.y }, { m_rect.size.x, 0 } });
        m_vertex.append({ m_rect.pos + m_rect.size - 1, m_rect.size });
        m_vertex.append({ { m_rect.pos.x, m_rect.pos.y + m_rect.size.y - 1 }, { 0, m_rect.size.y } });
    }
}
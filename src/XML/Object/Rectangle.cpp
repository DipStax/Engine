#include "XML/Object/Rectangle.hpp"

namespace eng::ui
{
    Rectangle::Rectangle(const std::string &_type, eng::Vector2<uint32_t> _size, eng::ThreadPool &_tp)
        : ContainerObject<RectangleEvent>(_type, _size, _tp), PositionX(*this, "PositionX", 0), PositionY(*this, "PositionY", 0),
          OriginX(*this, "OriginX", 0), OriginY(*this, "OriginY", 0), Rotation(*this, "Rotation", 0.f), Color(*this, "Color", { 255, 255, 255, 255 })
    {
        ownProperty();
    }

    Rectangle::Rectangle(const Rectangle &&_obj) noexcept
        : ContainerObject<RectangleEvent>(std::move(*_obj)), PositionX(std::move(_obj.PositionX)), PositionY(std::move(_obj.PositionY)),
          OriginX(std::move(_obj.OriginX)), OriginY(std::move(_obj.OriginY)), Rotation(std::move(_obj.Rotation)), Color(std::move(_obj.Color))
    {
        ownProperty();
        m_vertex = _obj.m_vertex;
        m_rect = _obj.m_rect;
    }

    Rectangle::~Rectangle()
    {
        unregisterProperty<uint32_t>(m_bind_posx);
        unregisterProperty<uint32_t>(m_bind_posy);
        unregisterProperty<uint32_t>(m_bind_originx);
        unregisterProperty<uint32_t>(m_bind_originy);
        unregisterProperty<float>(m_bind_scalex);
        unregisterProperty<float>(m_bind_scaley);
        unregisterProperty<float>(m_bind_rotation);
        unregisterProperty<eng::Color>(m_bind_color);
    }

    eng::Point2<uint32_t> Rectangle::getPosition() const
    {
        return { PositionX, PositionY };
    }

    eng::Point2<uint32_t> Rectangle::getOrigin() const
    {
        return { OriginX, OriginY };
    }

    void Rectangle::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        _target.draw(m_vertex.data(), m_vertex.size(), VertexArray::Type::Polygone);
    }

    void Rectangle::processRect()
    {
        m_rect = { getPosition() + getOrigin(), getSize() * getScale() };
        buildVertex();
    }

    void Rectangle::buildVertex()
    {
        m_vertex.clear();
        m_vertex.append({ m_rect.pos, { 0, 0 }, Color });
        m_vertex.append({ { m_rect.pos.x + m_rect.size.x, m_rect.pos.y }, { m_rect.size.x, 0 }, Color });
        m_vertex.append({ m_rect.pos + m_rect.size, m_rect.size, Color });
        m_vertex.append({ { m_rect.pos.x, m_rect.pos.y + m_rect.size.y }, { 0, m_rect.size.y }, Color });
    }

    void Rectangle::ownProperty()
    {
        registerProperty(PositionX);
        registerProperty(PositionY);
        registerProperty(OriginX);
        registerProperty(OriginY);
        registerProperty(ScaleX);
        registerProperty(ScaleY);
        registerProperty(Rotation);
        registerProperty(Color);

        m_bind_posx = bindProperty(PositionX);
        m_bind_posy = bindProperty(PositionY);
        m_bind_originx = bindProperty(OriginX);
        m_bind_originy = bindProperty(OriginY);
        m_bind_scalex = bindProperty(ScaleX);
        m_bind_scaley = bindProperty(ScaleY);
        m_bind_rotation = bindProperty(Rotation);
        m_bind_color = bindProperty(Color);
    }

    void Rectangle::onPositionChange(const Property<uint32_t>::Event &_pos)
    {
        std::ignore = _pos

        processRect();
    }

    void Rectangle::onOrigineChange(const Property<uint32_t>::Event &_ori)
    {
        std::ignore = _ori;

        processRect();
    }

    void Rectangle::onRotationChange(const Property<float>::Event &_rot)
    {
        std::ignore = _rot;

        processRect();
    }
}
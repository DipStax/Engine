#include "XML/Object/Rectangle.hpp"

namespace eng::ui
{   
    template<class ...Ts>
    Rectangle<Ts...>::Rectangle(const std::string &_type, eng::ThreadPool &_tp)
        : Object<Ts...>(_type, _tp), PositionX(*this, "PositionX", 0), PositionY(*this, "PositionY", 0),
          OriginX(*this, "OriginX", 0), OriginY(*this, "OriginY", 0), ScaleX(*this, "ScaleX", 1.f), ScaleY(*this, "ScaleY", 1.f),
          Rotation(*this, "Rotation", 0.f), Color(*this, "Color", eng::Color{ 255, 255, 255, 255 })
    {
        ownProperty();
    }

    Rectangle<Ts...>::Rectangle(Rectangle &&_obj) noexcept
        : Object<Ts...>(std::move(_obj)), PositionX(std::move(_obj.PositionX)), PositionY(std::move(_obj.PositionY)),
          OriginX(std::move(_obj.OriginX)), OriginY(std::move(_obj.OriginY)), ScaleX(std::move(_obj.ScaleX)), ScaleY(std::move(_obj.ScaleY)),
          Rotation(std::move(_obj.Rotation)), Color(std::move(_obj.Color))
    {
        ownProperty();
        m_vertex = _obj.m_vertex;
        m_rect = _obj.m_rect;
    }

    template<class ...Ts>
    Rectangle<Ts...>::~Rectangle()
    {
        unbindProperty<uint32_t>(m_bind_posx);
        unbindProperty<uint32_t>(m_bind_posy);
        unbindProperty<uint32_t>(m_bind_originx);
        unbindProperty<uint32_t>(m_bind_originy);
        unbindProperty<float>(m_bind_scalex);
        unbindProperty<float>(m_bind_scaley);
        unbindProperty<float>(m_bind_rotation);
        unbindProperty<eng::Color>(m_bind_color);
    }

    template<class ...Ts>
    eng::Point2<uint32_t> Rectangle<Ts...>::getPosition() const
    {
        return { PositionX, PositionY };
    }

    template<class ...Ts>
    eng::Point2<uint32_t> Rectangle<Ts...>::getOrigin() const
    {
        return { OriginX, OriginY };
    }

    template<class ...Ts>
    eng::Point2<float> Rectangle<Ts...>::getScale() const
    {
        return { ScaleX, ScaleY };
    }

    template<class ...Ts>
    void Rectangle<Ts...>::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        _target.draw(m_vertex.data(), m_vertex.size(), VertexArray::Type::Polygone);
    }

    template<class ...Ts>
    void Rectangle<Ts...>::ownProperty()
    {
        registerProperty(PositionX);
        registerProperty(PositionY);
        registerProperty(OriginX);
        registerProperty(OriginY);
        registerProperty(ScaleX);
        registerProperty(ScaleY);
        registerProperty(Rotation);
        registerProperty<eng::Color>(Color, [] (const std::string &_clr) {
            return eng::Color{ 255, 255, 255, 255 };
        });

        m_bind_posx = bindProperty(PositionX);
        m_bind_posy = bindProperty(PositionY);
        m_bind_originx = bindProperty(OriginX);
        m_bind_originy = bindProperty(OriginY);
        m_bind_scalex = bindProperty(ScaleX);
        m_bind_scaley = bindProperty(ScaleY);
        m_bind_rotation = bindProperty(Rotation);
        m_bind_color = bindProperty(Color);
    }

    template<class ...Ts>
    void Rectangle<Ts...>::processRect()
    {
        m_rect = { (getPosition() + getOrigin()).as<float>(), getSize().as<float>() * getScale() };
        buildVertex();
    }

    template<class ...Ts>
    void Rectangle<Ts...>::buildVertex()
    {
        m_vertex.clear();
        m_vertex.append({ m_rect.pos, { 0, 0 }, Color });
        m_vertex.append({ { m_rect.pos.x + m_rect.size.x, m_rect.pos.y }, { m_rect.size.x, 0 }, Color });
        m_vertex.append({ m_rect.pos + m_rect.size, m_rect.size, Color });
        m_vertex.append({ { m_rect.pos.x, m_rect.pos.y + m_rect.size.y }, { 0, m_rect.size.y }, Color });
    }

    template<class ...Ts>
    void Rectangle<Ts...>::onPositionChange(const Property<uint32_t>::Event &_pos)
    {
        std::ignore = _pos;

        processRect();
    }

    template<class ...Ts>
    void Rectangle<Ts...>::onOrigineChange(const Property<uint32_t>::Event &_ori)
    {
        std::ignore = _ori;

        processRect();
    }

    template<class ...Ts>
    void Rectangle<Ts...>::onRotationChange(const Property<float>::Event &_rot)
    {
        std::ignore = _rot;

        processRect();
    }
}
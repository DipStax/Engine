#include "XML/UI/TransformableObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    TransformableObject<Ts...>::TransformableObject(SysEventPool &_ep_sys, EventPool<Ts...> &_ep_cus, ThreadPool &_tp);
        : Object<Ts...>(_ep_sys, _ep_cus, _tp), m_trigger_uprop(_ep_cus.getTrigger<Property<uint32_t>::Event>()),
          m_trigger_fprop(_ep_cus.getTrigger<Property<float>::Event>()), m_trigger_rprop(_ep_cus.getTrigger<Property<Rect>::Event>())
    {
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    TransformableObject<Ts...>::~TransformableObject()
    {
        unbindProperty<uint32_t>(m_bind_height);
        unbindProperty<uint32_t>(m_bind_width);
        unbindProperty<uint32_t>(m_bind_posx);
        unbindProperty<uint32_t>(m_bind_posy);
        unbindProperty<float>(m_bind_scalex);
        unbindProperty<float>(m_bind_scaley);
        unbindProperty<float>(m_bind_rot);
        unbindProperty<Rect>(m_bind_rect);
    }


    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    void TransformableObject<Ts...>::setSize(const Point<uint32_t> &_size)
    {
        Height = _size.y;
        Width = _size.x;
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    constexpr Point2<uint32_t> TransformableObject<Ts...>::getSize() const
    {
        return { Width, Height };
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    void TransformableObject<Ts...>::setPosition(const Point<uint32_t> &_pos)
    {
        PositionX = _pos.x;
        PositionY = _pos.y;
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    void TransformableObject<Ts...>::move(const Point<uint32_t> &_mov)
    {
        PositionX += _mov.x;
        PositionY += _mov.y;
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    constexpr Point2<uint32_t> TransformableObject<Ts...>::getPosition() const
    {
        return { PositionX, PositionY };
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    void TransformableObject<Ts...>::setOrigin(const Point<uint32_t> &_org)
    {
        OriginX = _org.x;
        OriginY = _org.y;
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    constexpr Point2<uint32_t> TransformableObject<Ts...>::getOrigin() const
    {
        return { OriginX, OriginY };
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    void TransformableObject<Ts...>::setScale(const Point<float> &_scale)
    {
        ScaleX = _scale.x;
        ScaleY = _scale.y;
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    constexpr Point2<float> TransformableObject<Ts...>::getScale() const
    {
        return { ScaleX, ScaleY };
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    void TransformableObject<Ts...>::ownProperty()
    {
        registerProperty(Height);
        registerProperty(Width);
        registerProperty(PositionX);
        registerProperty(PositionY);
        registerProperty(OriginX);
        registerProperty(OriginY);
        registerProperty(ScaleX);
        registerProperty(ScaleY);
        registerProperty(Rotation);
        registerProperty<Rect>(Rect, [] (cosnt std::string &_rect) {
            return Rect{ { 0, 0 }, { 0, 0 } };
        });

        m_bind.add(Height, bindProperty, OnModified);
        m_bind.add(Width, bindProperty, OnModified);
        m_bind.add(PositionX, bindProperty, OnModified);
        m_bind.add(PositionY, bindProperty, OnModified);
        m_bind.add(OriginX, bindProperty, OnModified);
        m_bind.add(OriginY, bindProperty, OnModified);
        m_bind.add(ScaleX, bindProperty, OnModified);
        m_bind.add(ScaleY, bindProperty, OnModified);
        m_bind.add(Rotation, bindProperty, OnModified);
        m_bind.add(Rect, bindProperty);
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    PropertyBind<T> TransformableObject<Ts...>::OnModified(Property<T> &_prop)
    {
        return _prop.subscribe<T>(_prop, [*this] (const Property<T>::Event &_ev) {
            std::ignore = _ev;

            calculRect();
        });
    }

    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...>
    void TransformableObject<Ts...>::calculRect()
    {
        Rect = { getPosition() + getOrigin(), rect.size = getSize() * Scale };
        display();
    }
}
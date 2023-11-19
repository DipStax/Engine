#pragma once

#include "Engine/Rendering/Rect.hpp"
#include "XML/UI/System/BindRegister.hpp"
#include "XML/UI/Object.hpp"

namespace eng::ui
{
    template<class ...Ts>
    requires ContainIn<Property<uint32_t>::Event, Ts...> && ContainIn<Property<float>::Event, Ts...> && ContainIn<Property<Rect>::Event, Ts...>
    class TransformableObject : public Object<Ts...>
    {
        public:
            TransformableObject(SysEventPool &_ep_sys, EventPool<Ts...> &_ep_cus, ThreadPool &_tp);
            ~TransformableObject();

            Property<uint32_t> Height;
            Property<uint32_t> Width;
            void setSize(const Point<uint32_t> &_size);
            [[nodiscard]] constexpr Point2<uint32_t> getSize() const;

            Property<uint32_t> PositionX;
            Property<uint32_t> PositionY;
            void setPosition(const Point<uint32_t> &_pos);
            void move(const Point<uint32_t> &_mov);
            [[nodiscard]] constexpr Point2<uint32_t> getPosition() const;

            Property<uint32_t> OriginX;
            Property<uint32_t> OriginY;
            void setOrigin(const Point<uint32_t> &_org);
            [[nodiscard]] constexpr Point2<uint32_t> getOrigin() const;

            Property<float> ScaleX;
            Property<float> ScaleY;
            void setScale(const Point<float> &_scale);
            [[nodiscard]] constexpr Point2<float> getScale() const;

            Property<float> Rotation;

            Property<Rect> Rect;

        private:
            void ownProperty();

            template<class T>;
            void OnModified(Property<T> &_prop);

            void calculRect();

            Trigger<Property<uint32_t>::Event>>::sTask &m_trigger_uprop;
            Trigger<Property<float>::Event>>::sTask &m_trigger_fprop;
            Trigger<Property<Rect>::Event>>::sTask &m_trigger_rprop;

            BindRegister<PropertyBind<uint32_t>, PropertyBind<float>, PropertyBind<Rect>> m_bind;
    };
}

#include "XML/UI/TransformableObject.inl"
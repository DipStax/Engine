#pragma once

#include "XML/UI/EventObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    using PropertyEvent = typename unique_type<Ts...>::type;

    template<class T>
    using PropertyBind = Trigger<typename Property<T>::Event>::sTask;

    template<class ...Ts>
    class PropertyObject;

    template<class ...Ts>
    class PropertyObject<std::tuple<Ts...>> : public EventObject<PropertyEvent<Ts...>>
    {
        public:
            PropertyObject(ThreadPool &_tp);
            PropertyObject(PropertyObject<Ts...> &&_obj) noexcept;
            ~PropertyObject() = default;

        protected:
            template<class T>
            requires ContainIn<typename Property<T>::Event, Ts...>
            [[nodiscard]] PropertyBind<T> bindProperty(Property<T> &_prop);

            template<class T>
            requires ContainIn<typename Property<T>::Event, Ts...>
            void unbindProperty(PropertyBind<T> _stask);
    };
}

#include "XML/UI/PropertyObject.inl"
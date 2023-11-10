#pragma once

#include "XML/UI/EventObject.hpp"

namespace eng::ui
{
    template<class T>
    using PropertyBind = Trigger<typename Property<T>::Event>::sTask;

    template<class ...Ts>
    class PropertyBinder
    {
        public:
            PropertyBinder(EventPool<Ts...> &_ep_cus);
            // PropertyBinder(PropertyBinder<std::tuple<Ts...>> &&_obj) noexcept;
            ~PropertyBinder() = default;

        protected:
            template<class T>
            requires ContainIn<typename Property<T>::Event, Ts...>
            [[nodiscard]] PropertyBind<T> bindProperty(Property<T> &_prop);

            template<class T>
            requires ContainIn<typename Property<T>::Event, Ts...>
            void unbindProperty(PropertyBind<T> _stask);

        private:
            EventPool<Ts...> &_ep_cus;
    };
}

#include "XML/UI/PropertyBinder.inl"
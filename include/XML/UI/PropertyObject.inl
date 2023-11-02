#include "XML/UI/PropertyObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    PropertyObject<std::tuple<Ts...>>::PropertyObject(ThreadPool &_tp)
        : EventObject<Ts...>(_tp)
    {
    }

    template<class ...Ts>
    PropertyObject<std::tuple<Ts...>>::PropertyObject(PropertyObject<Ts...> &&_obj) noexcept
        : EventObject<Ts...>(std::move(*this))
    {
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<typename Property<T>::Event, Ts...>
    PropertyBind<T> PropertyObject<std::tuple<Ts...>>::bindProperty(Property<T> &_prop)
    {
        return _prop.subscribe([this] (const Property<T>::Event &_val) {
            this->raise<Property<T>::Event>(_val);
        });
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<typename Property<T>::Event, Ts...>
    void PropertyObject<std::tuple<Ts...>>::unbindProperty(PropertyBind<T> _stask)
    {
        unsubscribe<Property<T>::Event>(_stask);
    }
}
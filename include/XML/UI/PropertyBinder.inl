#include "XML/UI/PropertyBinder.hpp"

namespace eng::ui
{
    template<class ...Ts>
    PropertyBinder<Ts...>::PropertyBinder(EventPool<Ts...> &_ep_cus)
        : m_ep_cus(_ep_cus)
    {
    }

    // template<class ...Ts>
    // PropertyBinder<std::tuple<Ts...>>::PropertyBinder(PropertyBinder<std::tuple<Ts...>> &&_obj) noexcept
    //     : EventObject<PropertyEvent<Ts...>>(std::move(*this))
    // {
    // }

    template<class ...Ts>
    template<class T>
    requires ContainIn<typename Property<T>::Event, Ts...>
    PropertyBind<T> PropertyBinder<Ts...>::bindProperty(Property<T> &_prop)
    {
        return _prop.subscribe([this] (const Property<T>::Event &_val) {
            this->m_ep_cus.template raise<typename Property<T>::Event>(_val);
        });
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<typename Property<T>::Event, Ts...>
    void PropertyBinder<Ts...>::unbindProperty(PropertyBind<T> _stask)
    {
        m_ep_cus.template unsubscribe<typename Property<T>::Event>(_stask);
    }
}
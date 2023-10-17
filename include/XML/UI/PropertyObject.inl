#include "XML/UI/PropertyObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    PropertyObject<Ts...>::PropertyObject(ThreadPool &_tp)
        : EventObject<Ts...>(_tp)
    {
    }

    template<class ...Ts>
    PropertyObject<Ts...>::PropertyObject(PropertyObject<Ts...> &&_obj) noexcept
        : EventObject<Ts...>(std::move(*this)), m_conv(std::move(_obj.m_conv))
    {
    }

    template<class ...Ts>
    void PropertyObject<Ts...>::registerProperty(Property<std::string> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = _val;
        };
    }

    template<class ...Ts>
    template<IsUnsigned T>
    void PropertyObject<Ts...>::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stoull(_val));
        };
    }

    template<class ...Ts>
    template<IsSigned T>
    void PropertyObject<Ts...>::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stoll(_val));
        };
    }

    template<class ...Ts>
    template<IsFPN T>
    void PropertyObject<Ts...>::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stod(_val));
        };
    }

    template<class ...Ts>
    template<class T>
    void PropertyObject<Ts...>::registerProperty(Property<T> &_prop, fn_conv<T> _conv)
    {
        m_conv[_prop.getName()] = [&_prop, _conv] (const std::string &_val) {
            _prop = _conv(_val);
        };
    }

    template<class ...Ts>
    template<class T>
    Property<T>::PropTrigger::sTask PropertyObject<Ts...>::bindProperty(Property<T> &_prop)
    {
        return _prop.subscribe([this] (const Property<T>::Event& _val) {
            this->raise<Property<T>::Event>(_val);
        });
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<typename Property<T>::Event, Ts...>
    void PropertyObject<Ts...>::unregisterProperty(Property<T>::PropTrigger::sTask _stask)
    {
        unsubscribe<Property<T>::Event>(_stask);
    }

    template<class ...Ts>
    void PropertyObject<Ts...>::setProperty(const std::string &_name, const std::string &_val)
    {
        if (m_conv.contains(_name))
            m_conv[_name](_val);
        // handle non registered class
    }
}
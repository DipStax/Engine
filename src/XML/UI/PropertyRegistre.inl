#include "XML/UI/PropertyRegistre.hpp"

namespace eng::ui
{
    void PropertyRegistre::registerProperty(Property<std::string> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = _val;
        };
    }

    template<IsUnsigned T>
    void PropertyRegistre::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stoull(_val));
        };
    }

    template<IsSigned T>
    void PropertyRegistre::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stoll(_val));
        };
    }

    template<IsFPN T>
    void PropertyRegistre::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stod(_val));
        };
    }

    template<class T>
    void PropertyRegistre::registerProperty(Property<T> &_prop, fn_conv<T> _conv)
    {
        m_conv[_prop.getName()] = [&_prop, _conv] (const std::string &_val) {
            _prop = _conv(_val);
        };
    }

    template<class ...Ts>
    void PropertyObject<std::tuple<Ts...>>::setProperty(const std::string &_name, const std::string &_val)
    {
        if (m_conv.contains(_name))
            m_conv[_name](_val);
        // handle non registered class
    }
}
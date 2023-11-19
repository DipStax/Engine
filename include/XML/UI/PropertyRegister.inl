#include <string>

#include "XML/UI/PropertyRegister.hpp"

namespace eng::ui
{
    template<IsUnsigned T>
    void PropertyRegister::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stoull(_val));
        };
    }

    template<IsSigned T>
    void PropertyRegister::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stoll(_val));
        };
    }

    template<IsFPN T>
    void PropertyRegister::registerProperty(Property<T> &_prop)
    {
        m_conv[_prop.getName()] = [&_prop] (const std::string &_val) {
            _prop = static_cast<T>(std::stod(_val));
        };
    }

    template<class T>
    void PropertyRegister::registerProperty(Property<T> &_prop, fn_conv<T> _conv)
    {
        m_conv[_prop.getName()] = [&_prop, _conv] (const std::string &_val) {
            _prop = _conv(_val);
        };
    }
}
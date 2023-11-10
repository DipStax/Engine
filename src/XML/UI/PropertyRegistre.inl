#include "XML/UI/PropertyRegister.hpp"

namespace eng::ui
{
    void PropertyRegister::setProperty(const std::string &_name, const std::string &_val)
    {
        if (m_conv.contains(_name))
            m_conv[_name](_val);
        // handle non registered class
    }
}
#pragma once

#include "XML/UI/PropertyBinder.hpp"
#include "XML/UI/PropertyRegister.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class PropertyObject : public PropertyBinder<Ts...>, public PropertyRegister
    {
        public:
            PropertyObject(EventPool<Ts...> &_ep_cus);
            ~PropertyObject() = default;
    };
}
#include "XML/UI/PropertyObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    PropertyObject<Ts...>::PropertyObject(EventPool<Ts...> &_ep_cus)
        : PropertyBinder<Ts...>(_ep_cus)
    {
    }
}
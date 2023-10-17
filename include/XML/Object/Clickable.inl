#include "XML/Object/Clickable.hpp"

namespace eng::ui
{
    template<class ...Ts>
    requires ContainIn<eng::Event::MouseButton, Ts...>
    Clickable<Ts...>::Clickable(eng::PoolEvent<Ts...> &_pe)
    {
        m_stask = _pe.subscribe<eng::Event::MouseButton>(onClik);
    }

    template<class ...Ts>
    requires ContainIn<eng::Event::MouseButton, Ts...>
    Clickable<Ts...>::Clickable(eng::PoolEvent<Ts...> &_pe)
    {
        _pe.unsubscribe<eng::Event::MouseButton>(m_stask);
    }
}
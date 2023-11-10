#include "XML/UI/Event/Clickable.hpp"

namespace eng::ui
{
    template<class T>
    requires BasedOf<Object, T>
    template<class ..._Ts>
    requires ContainIn<Click, _Ts...>
    Clickable<T>::Clickable(SysEventPool &_sys_ep, EventPool<_Ts...> &_cus_ep, int8_t _accept)
        : m_accept(_accept), m_trigger_click(_cus_ep.template getTrigger<T>()),
          m_trriger_mb(_sys_ep.template getTrigger<FromEvent>()),
    {
        m_task = m_sys_ep.template redistribuet<Event>(ClickEvent);
    }

    template<class T>
    requires BasedOf<Object, T>
    Clickable<T>::Clickable()
    {
        m_task_mb.template unsubscribe<Event>(m_task_mb);
    }

    template<class T>
    requires BasedOf<Object, T>
    bool Clickable<T>::click(const Click &_clic)
    {
        // check clic is inside the actual object
        if (_clic.state & m_accept) {
            onClick(_clic);
            m_task_clic.template raise<Event>(_clic);
            return true;
        }
        return false;
    }
}
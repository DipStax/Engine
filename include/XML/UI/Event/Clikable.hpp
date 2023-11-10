#pragma once

namespace eng::ui
{
    class Clickable
    {
        public:
            using FromEvent = Event::MouseButton;
            using Event = evt::Click;

            template<class ...Ts>
            requires ContainIn<FromEvent, Ts...>
            Clickable(SysEventPool &_sys_ep, EventPool<Ts...> &_cus_ep, int8_t _accept = 0);
            ~Clickable();

        protected:
            virtual void onClick(const Click &) = 0;

        private:
            int8_t m_accept;

            Trigger<Event> &m_trigger_click;
            Trigger<FromEvent> &m_trigger_mb;
            Trigger<FromEvent>::sTask m_task_mb = nullptr;
    }
}
#pragma once

#include "XML/UI/System/Expression.hpp"
#include "XML/UI/ContainerObject.hpp"
#include "XML/UI/EventObject.hpp"
#include "XML/UI/PropertyObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class Object : public EventObject<Ts...>, public PropertyObject<Ts...>, ContainerObject<Ts...>
    {
        public:
            Object(EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, const std::string &_name, ThreadPool &_tp);
            ~Object();

        private:
            template<class T>
            requires ContainIn<T, Ts...>
            void transferEvent(const T &_event);

            template<class T, _Ts...>
            requires ContainIn<T, Ts...>
            void bindEventPool(EventPool<Ts...> &_ep_cus);
            template<class T>
            requires ContainIn<T, Ts...>
            void bindEventPool(EventPool<Ts...> &_ep_cus);

            template<class T, _Ts...>
            requires ContainIn<T, SysEventType>
            void bindEventPool(EventPool<T, _Ts...> &_ep_sys);
            template<class T>
            requires ContainIn<T, SysEventType>
            void bindEventPool(EventPool<T> &_ep_sys);

            std::tuple<Trigger<Ts>::sTask...> m_task_cus;
            SysTriggerTuple m_task_sys;

            const std::string m_name;
    }
}
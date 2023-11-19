#pragma once

#include "Engine/Rendering/IDrawable.hpp"

#include "XML/UI/System/Expression.hpp"
#include "XML/UI/ContainerObject.hpp"
#include "XML/UI/EventObject.hpp"
#include "XML/UI/PropertyObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class Object : public EventObject<Ts...>, public PropertyObject<Ts...>, public ContainerObject<Ts...>, public IDrawable
    {
        public:
            Object(EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, const std::string &_name, ThreadPool &_tp);
            ~Object();

        protected:
            virtual void display() = 0;

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

            BindRegister<Ts...> m_bind_cus;
            SysBindRegister m_bind_sys;

            const std::string m_name;
    }
}
#pragma once

#include <memory>

#include "Engine/Event/EventPool.hpp"
#include "XML/UI/System/Expression.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class Object;

    template<class ...Ts>
    class ContainerObject
    {
        public:
            ContainerObject(EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, ThreadPool &_tp)
            ~ContainerObject() = default;

            template<class T>
            requires IsBasedOf<Object<Ts...>, T>
            std::shared_ptr<Object<Ts...>> addContent(const std::string &_type);
            template<class T, class ..._Ts>
            requires IsBasedOf<Object<Ts...>, T> && AcceptCtr<T, EventPool<Ts...>, SysEventPool &, const std::string &, ThreadPool &>;
            std::shared_ptr<Object<Ts...>> addContent(const std::string &_type);

        private:
            EventPool<Ts...> &m_ep_cus;
            SysEventPool &m_ep_sys;
            ThreadPool &m_tp;

            std::vector<std::shared_ptr<Object<Ts...>> m_content;
    };
}
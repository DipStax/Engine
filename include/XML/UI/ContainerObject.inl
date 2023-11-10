#include "XML/UI/ContainerObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    ContainerObject<Ts...>::ContainerObject(EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, ThreadPool &_tp)
        : m_ep_cus(_ep_cus), m_ep_sys(_ep_sys), m_tp(_tp)
    {
    }

    template<class ...Ts>
    template<class T>
    requires IsBasedOf<Object<Ts...>, T>
    std::shared_ptr<Object<Ts...>> ContainerObject<Ts...>::addContent(const std::string &_type);
    {
        Factory::Balise
        m_content.push_back(std::make_shared<T>(m_ep_cus, m_ep_sys, _type, m_tp));
        return m_content.back();
    }

    template<class T, class ...Ts>
    requires IsBasedOf<Object<Ts...>, T> && AcceptCtr<T, EventPool<Ts...>, SysEventPool &, const std::string &, ThreadPool &, _Ts ...&&>;
    std::shared_ptr<Object<Ts...>> ContainerObject<Ts...>::addContent(const std::string &_type, _Ts ...&&_args)
    {
        m_content.push_back(std::make_shared<T>(m_ep_cus, m_ep_sys, _type, m_tp, std::foward<_Ts>(_args)...));
        return m_content.back();
    }
}
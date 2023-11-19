#include "XML/Factory/Balise.hpp"

namespace eng::Factory
{
    template<class ...Ts, class ..._Ts>
    std::shared_ptr<typename Balise<std::tuple<Ts...>, std::tuple<_Ts...>>::BaseType> Balise<std::tuple<Ts...>, std::tuple<_Ts...>>::build(const xml::Balise &_balise, EventPool<Ts...> &_ep_cus, ::eng::ui::SysEventPool &_ep_sys, ThreadPool &_tp) const
    {
        std::shared_ptr<ui::Object> balise = build(_balise.getType(), _ep_cus, _ep_sys, _tp);

        for (const xml::Value &[_key, _val] : _balise->getValue())
            balise->setProperty(_key, _val);
        for (const xml::Balise &_sub : _balise.getChild())
            internalAddContent(balise);
        return balise;
    }

    template<class ...Ts, class ..._Ts>
    std::shared_ptr<typename Balise<std::tuple<Ts...>, std::tuple<_Ts...>>::BaseType> Balise<std::tuple<Ts...>, std::tuple<_Ts...>>::build(const std::string &_type, EventPool<Ts...> &_ep_cus, ::eng::ui::SysEventPool &_ep_sys, ThreadPool &_tp) const
    {
        return internalBuild(_type, _type, _ep_cus, _ep_sys, _tp);
    }

    template<class ...Ts, class ..._Ts>
    template<class ...__Ts>
    std::shared_ptr<typename Balise<std::tuple<Ts...>, std::tuple<_Ts...>>::BaseType> Balise<std::tuple<Ts...>, std::tuple<_Ts...>>::internalAddContent(std::shared_ptr<BaseType> _base, const std::string &_type) const
    {
        return nullptr;
    }

    template<class ...Ts, class ..._Ts>
    template<IsPair _T, class ...__Ts>
    std::shared_ptr<typename Balise<std::tuple<Ts...>, std::tuple<_Ts...>>::BaseType> Balise<std::tuple<Ts...>, std::tuple<_Ts...>>::internalAddContent(std::shared_ptr<BaseType> _base, const std::string &_type) const
    {
        if (std::string(_T::second) == _type)
            return _base->template addContent<_T>(_type);
        return internalAddContent<__Ts...>(_type, _args);
    }
}
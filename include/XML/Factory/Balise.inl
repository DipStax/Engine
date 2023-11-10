#include "XML/Factory/Balise.hpp"
#include "XML/UI/PropertyRegistre.hpp"

namespace eng::Factory
{
    template<class ...Ts, class ..._Ts>
    std::shared_ptr<BaseType> Balise<Ts...>::build(const xml::Balise &_balise, EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, ThreadPool &_tp) const
    {
        std::shared_ptr<ui::Object> balise = Balise<Ts...>::build(_balise.getName(), _tp);

        for (const xml::Value &[_key, _val] : _balise->getValue())
            propreg->setProperty(_key, _val);
        for (const xml::Balise &_sub : _balise.getChild())
            addContent(balise);
        return balise;
    }

    template<class ...Ts>
    std::shared_ptr<BaseType> Balise<Ts...>::build(const std::string &_type, EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, ThreadPool &_tp) const
    {
        std::shared_ptr<ui::Object> balise = internalBuild(_type, _type, _ep_cus, _ep_sys, _tp);

        for (const xml::Value &[_key, _val] : propreg->getValue())
            balise->setProperty(_key, _val);
    }

    template<class ...Ts>
    std::shared_ptr<Balise<Ts...>::BaseType> Balise<Ts...>::appendObject(std::shared_ptr<ui::Object> _base, const std::string &_balise) const
    {
        return internalAddContent<_Ts...>(_base, _type);
    }

    template<class ...__Ts>
    std::shared_ptr<Balise<Ts...>::BaseType> Balise<Ts...>::internalAddContent(std::shared_ptr<BaseType> _base, const std::string &_type) const
    {
        return nullptr;
    }

    template<IsPair _T, class ...__Ts>
    std::shared_ptr<Balise<Ts...>::BaseType> Balise<Ts...>::internalAddContent(std::shared_ptr<BaseType> _base, const std::string &_type) const
    {
        if (std::string(_T::second) == _type)
            return _base->template addContent<_T>(_type);
        return internalAddContent<__Ts...>(_type, _args);
    }
}
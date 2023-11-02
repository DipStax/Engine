#include "XML/Factory/Balise.hpp"
#include "XML/UI/PropertyRegistre.hpp"

namespace eng::Factory
{
    template<class ...Ts>
    Balise<Ts...>::Balise(ThreadPool &_tp)
        : m_tp(_tp)
    {
    }

    template<class ...Ts>
    std::shared_ptr<ui::ObjectRegistre> Balise<Ts...>::build(const xml::Balise &_balise) const
    {
        std::shared_ptr<ui::BaseObject> balise = build(_balise.getName());

        for (xml::Value [_key, _val] : propreg->getValue())
            propreg->setProperty(_key, _val);
        return balise;
    }

    template<class ...Ts>
    std::shared_ptr<ui::ObjectRegistre> Balise<Ts...>::build(const std::string &_type) const
    {
        return internalBuild(_type, _type, m_tp);
    }
}
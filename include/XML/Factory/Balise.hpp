#pragma once

#include "Tool/PreProcessing.hpp"
#include "XML/Factory/Base.hpp"
#include "XML/UI/ContainerObject.hpp"
#include "XML/UI/System/Expression.hpp"
#include "XML/Balise.hpp"-

namespace eng::Factory
{
    template<class ...Ts>
    class Balise;

    template<class ...Ts, class ..._Ts>
    class Balise<std::tuple<Ts...>, std::tuple<_Ts...>> : public Base<ui::Object<Ts...>, std::tuple<_Ts...>, const std::string &, EventPool<Ts...> &, ::eng::ui::SysEventPool &, ThreadPool &>
    {
        public:
            using BaseFactory = Base<ui::Object<Ts...>, std::tuple<_Ts...>, const std::string &, EventPool<Ts...> &, ::eng::ui::SysEventPool &, ThreadPool &>;
            using BaseType = BaseFactory::BaseType;

            Balise() = default;
            ~Balise() = default;

            std::shared_ptr<BaseType> build(const xml::Balise &_balise, EventPool<Ts...> &_ep_cus, ::eng::ui::SysEventPool &_ep_sys, ThreadPool &_tp) const;

            std::shared_ptr<BaseType> build(const std::string &_type, EventPool<Ts...> &_ep_cus, ::eng::ui::SysEventPool &_ep_sys, ThreadPool &_tp) const;

        private:
            std::shared_ptr<BaseType> addContent(const std::string &_balise, ThreadPool &_tp) const;

            template<class ...__Ts>
            std::shared_ptr<BaseType> internalAddContent(std::shared_ptr<BaseType> _base, const std::string &_type) const;
            template<IsPair _T, class ...__Ts>
            std::shared_ptr<BaseType> internalAddContent(std::shared_ptr<BaseType> _base, const std::string &_type) const;
    };
}

#include "XML/Factory/Balise.inl"
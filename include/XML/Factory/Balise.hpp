#pragma once

#include "Tool/PreProcessing.hpp"
#include "XML/Factory/Base.hpp"
#include "XML/UI/ObjectRegistre.hpp"

namespace eng::Factory
{
    namespace imp
    {
        template<class ...Ts, class ..._Ts>
        class Balise : public BaseFactory<ui::Object<Ts...>, std::tuple<_Ts...>, EventPool<Ts...> &, SysEventPool &, const std::string &, ThreadPool &>
        {
            public:
                Balise() = default;
                ~Balise() = default;

                std::shared_ptr<BaseType> build(const xml::Balise &_balise, EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, ThreadPool &_tp) const;

                std::shared_ptr<BaseType> build(const std::string &_type, EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, ThreadPool &_tp) const;

            private:
                std::shared_ptr<BaseType> addContent(const std::string &_balise, ThreadPool &_tp) const;

                template<class ...__Ts>
                std::shared_ptr<BaseType> internalAddContent(std::shared_ptr<BaseType> _base, const std::string &_type) const;
                template<IsPair _T, class ...__Ts>
                std::shared_ptr<BaseType> internalAddContent(std::shared_ptr<BaseType> _base, const std::string &_type) const;
        };
    }

    template<class ...Ts>
    class Balise
    {
        public:
            [[nodiscard]] static const Balise &instance() const;

        private:
            Balise() = default;
            ~Balise() = default;

            static Balise m_balise;
    }
}

#include "XML/Factory/Base.hpp"
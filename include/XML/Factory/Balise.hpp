#pragma once

#include "Tool/PreProcessing.hpp"
#include "XML/Factory/Base.hpp"
#include "XML/UI/ObjectRegistre.hpp"

namespace eng::Factory
{
    template<class ...Ts>
    class Balise : public BaseFactory<ui::BaseObject, std::tuple<Ts...>, const std::string &, ThreadPool &>
    {
        public:
            Balise(ThreadPool &_tp);
            ~Balise() = default;

            std::shared_ptr<ui::BaseObject> build(const xml::Balise &_balise) const;

            std::shared_ptr<ui::BaseObject> build(const std::string &_type) const;

        private:
            ThreadPool &m_tp;
    };
}

#include "XML/Factory/Base.hpp"
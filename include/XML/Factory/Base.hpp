#pragma once

#include <memory>

#include "Tool/PreProcessing.hpp"

namespace eng::Factory
{
    template<class ...Ts>
    class Base;

    template<AcceptCtr T, class ...Ts, class ..._Ts>
    requires IsFacMap<T, std::tuple<Ts...>> && TupleAcceptCtr<Ts..., _Ts...>
    class Base<T, std::tuple<Ts...>, _Ts...>
    {
        public:
            template<class _T, class ...__Ts>
            requires ContainIn<_T, typename pair_key<_Ts...>::type>
            std::shared_ptr<_T> build(__Ts ...&&_arg) const;

        protected:
            std::shared_ptr<T> internalBuild(const std::string &_type, _Ts ...&&_arg) const;

        private:
            template<class ...__Ts>
            std::shared_ptr<T> internalBuild(const std::string &_type, _Ts ...&&_args) const;
            template<IsPair _T, class ...__Ts>
            std::shared_ptr<T> internalBuild(const std::string &_type, _Ts ...&&_args) const;
    };
}

#include "XML/Factory/Base.hpp"
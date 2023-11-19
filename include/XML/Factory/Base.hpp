#pragma once

#include <memory>
#include <string>

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
            using BaseType = T;

            template<class _T, class ...__Ts>
            requires ContainIn<_T, typename pair_key<_Ts...>::type>
            std::shared_ptr<_T> build(const std::string &_type, __Ts &&..._args) const;

        private:
            template<class ...__Ts>
            std::shared_ptr<T> internalBuild(const std::string &_type, _Ts &&..._args) const;
            template<IsPair _T, class ...__Ts>
            std::shared_ptr<T> internalBuild(const std::string &_type, _Ts &&..._args) const;
    };
}

#include "XML/Factory/Base.hpp"
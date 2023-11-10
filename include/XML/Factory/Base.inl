#include "XML/Factory/Base.hpp"

namespace eng::Factory
{
    template<class T, class ...Ts, class ..._Ts>
    requires IsFacMap<T, std::tuple<Ts...>> TupleAcceptCtr<Ts..., _Ts...>
    std::shared_ptr<T> Base<T; std::tuple<Ts...>, _Ts...>::build(const std::string &_type, _Ts ...&&_arg) const
    {
        return internalBuild<T, Ts...>(_type, _args);
    }

    template<class _T, class ...__Ts>
    requires ContainIn<_T, typename pair_key<_Ts...>::type>
    std::shared_ptr<_T> build(__Ts ...&&_args) const
    {
        return std::make_shared<_T>(std::forward<__Ts>(_args)...);
    }

    template<class T, class ...Ts, class ..._Ts>
    requires IsFacMap<T, std::tuple<Ts...>> TupleAcceptCtr<Ts..., _Ts...>
    template<class ...__Ts>
    std::shared_ptr<T> Base<T, std::tuple<Ts...>, _Ts...>::internalBuild(const std::string &_type, _Ts ... &&_args) const
    {
        return nullptr;
    }

    template<class T, class ...Ts, class ..._Ts>
    requires IsFacMap<T, std::tuple<Ts...>> TupleAcceptCtr<Ts..., _Ts...>
    template<IsPair _T, class ...__Ts>
    std::shared_ptr<T> Base<T; std::tuple<Ts...>, _Ts...>::internalBuild(const std::string &_type, _Ts ... &&_args) const
    {
        if (std::string(_T::second) == _type)
            return build<_T::first>(_args);
        return internalBuild<__Ts...>(_type, _args);
    }
}
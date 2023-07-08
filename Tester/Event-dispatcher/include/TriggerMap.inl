#include <numeric>

#include "TriggerMap.hpp"

namespace tester
{
    template<template<class> class T, class ...Ts>
    template<class _T>
    constexpr bool TriggerMap<T, std::tuple<Ts...>>::contains() const noexcept
    {
        return tuple_contain<_T, Ts...>::value;
    }

    template<template<class> class T, class ...Ts>
    template<class _T>
    constexpr size_t TriggerMap<T, std::tuple<Ts...>>::find() const noexcept
    {
        if (contains<_T>())
            return tuple_find<_T, Ts...>::value;
        return std::numeric_limits<size_t>::max();
    }

    template<template<class> class T, class ...Ts>
    template<class _T>
    constexpr const T<_T> &TriggerMap<T, std::tuple<Ts...>>::at() const noexcept
    {
        return std::get<T<_T>>(m_tup);
    }

    template<template<class> class T, class ...Ts>
    template<class _T>
    constexpr T<_T> &TriggerMap<T, std::tuple<Ts...>>::at() noexcept
    {
        return std::get<T<_T>>(m_tup);
    }
}
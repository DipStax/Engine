#pragma once

#include <type_traits>
#include <tuple>
#include <map>
#include <cstddef>

#include "Engine/System/ThreadPool.hpp"

template<class T, class ...Ts>
struct tuple_contain;

template<class T, class _T, class ...Ts>
struct tuple_contain<T, _T, Ts...>
{
    static constexpr bool value = std::is_same<T, _T>::value || tuple_contain<T, Ts...>::value;
};

template<class T, class _T>
struct tuple_contain<T, _T>
{
    static constexpr bool value = std::is_same<T, _T>::value;
};

namespace imp
{
    template<size_t I, class T, class ...Ts>
    struct tuple_find;

    template<size_t I, class T, class _T, class ...Ts>
    struct tuple_find<I, T, _T, Ts...>
    {
        static constexpr size_t value = std::is_same<T, _T>::value ? I : imp::tuple_find<I, T, Ts...>::value;
    };

    template<size_t I, class T, class _T>
    struct tuple_find<I, T, _T>
    {
        static constexpr size_t value = std::is_same<T, _T>::value ? I : I + 1;
    };
}

template<class T, class ...Ts>
struct tuple_find
{
    static constexpr size_t value = imp::tuple_find<0, T, Ts...>::value;
};

template<class ...Ts>
struct tuple_size;

template<class T, class ...Ts>
struct tuple_size<T, Ts...>
{
    static constexpr size_t value = 1 + tuple_size<Ts...>::value;
};

template<class T>
struct tuple_size<T>
{
    static constexpr size_t value = 1;
};

template<class, class>
struct tuple_append;

template<class T, class ...Ts>
struct tuple_append<T, std::tuple<Ts...>>
{
    using type = std::tuple<T, Ts...>;
};

template<template<class> class T, class ...Ts>
struct tuple_apply_template;

template<template<class> class T, class _T, class ...Ts>
struct tuple_apply_template<T, _T, Ts...>
{
    using type = typename tuple_append<T<_T>, typename tuple_apply_template<T, Ts...>::type>::type;
};

template<template<class> class T, class _T>
struct tuple_apply_template<T, _T>
{
    using type = std::tuple<T<_T>>;
};

namespace eng
{
    template<template<class> class T, class ...Ts>
    class TriggerMap;

    template<template<class> class T, class ...Ts>
    class TriggerMap<T, std::tuple<Ts...>>
    {
        public:
            TriggerMap(ThreadPool &_tp);
            ~TriggerMap() = default;

            template<class _T>
            constexpr bool contains() const noexcept;

            template<class _T>
            constexpr size_t find() const noexcept;

            template<class _T>
            [[nodiscard]] constexpr const T<_T> &at() const noexcept;
            template<class _T>
            [[nodiscard]] constexpr T<_T> &at() noexcept;

        private:
            typename tuple_apply_template<T, Ts...>::type m_tup;
    };
}
#include "TriggerMap.inl"
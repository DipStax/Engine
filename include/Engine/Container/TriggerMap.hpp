#pragma once

#include <type_traits>
#include <tuple>
#include <map>
#include <cstddef>

#include "Engine/System/ThreadPool.hpp"
#include "Tool/PreProcessing.hpp"

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
            //tuple_apply_template<T, Ts...>::type m_tup;
            std::tuple<T<Ts>...> m_tup;
    };
}

#include "Engine/Container/TriggerMap.inl"
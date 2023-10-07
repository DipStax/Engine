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
            TriggerMap(TriggerMap<T, std::tuple<Ts...>> &&_tm) noexcept;
            ~TriggerMap() = default;

            template<class _T>
            constexpr size_t find() const noexcept requires ContainIn<_T, Ts..>;

            template<class _T>
            [[nodiscard]] constexpr const T<_T> &at() const noexcept requires ContainIn<_T, Ts..>;
            template<class _T>
            [[nodiscard]] constexpr T<_T> &at() noexcept requires ContainIn<_T, Ts..>;

        private:
            using TriggerMapImp = typename tuple_apply_template<T, Ts...>::type;
            std::tuple<T<Ts>...> m_tup;
            // TriggerMapImp m_tup;
    };
}
#include "TriggerMap.inl"
#pragma once

#include <optional>
#include <tuple>
#include <type_traits>

#include "Tool/Export.hpp"

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

template<class ...Ts>
struct unpack_tuple;

template<class, class>
struct tuple_prepend;

template<class T, class ...Ts>
struct tuple_prepend<T, std::tuple<Ts...>>
{
    using type = std::tuple<T, Ts...>;
};

template<class, class>
struct tuple_cat;

template<class ...Ts, class ..._Ts>
struct tuple_cat<std::tuple<Ts...>, std::tuple<_Ts...>>
{
    using type = std::tuple<Ts..., _Ts...>;
};

namespace imp
{
    template<class ...Ts>
    struct unpack_tuple;

    template<class ...Ts, class ..._Ts>
    struct unpack_tuple<std::tuple<Ts...>, _Ts...>
    {
        using type = typename tuple_cat<Ts..., typename unpack_tuple<_Ts...>::type>::type;
    };

    template<class T, class ...Ts>
    struct unpack_tuple<T, Ts...>
    {
        using type = typename tuple_prepend<T, typename unpack_tuple<Ts...>::type>::type;
    };

    template<class T>
    struct unpack_tuple<T>
    {
        using type = std::tuple<T>;
    };
}

template<class ...Ts>
struct unpack_tuple<std::tuple<Ts...>>
{
    using type = typename imp::unpack_tuple<Ts...>::type;
};

namespace ecs::sys
{
    class ISystem;
}

template<class ...Ts>
using Tuple = std::tuple<std::optional<Ts>...>;

namespace opt
{
    template<class T, class ...Ts>
    std::optional<T> &get(Tuple<Ts...> &_tuple) noexcept
    {
        return std::get<std::optional<T>>(_tuple);
    }
}

template<template<typename...> class base, typename derived>
struct is_base_of_template_impl
{
    template<typename... Ts>
    static constexpr std::true_type  test(const base<Ts...> *);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<derived*>()));
};

template<template<typename ...> class base, typename derived>
using is_base_of_template = typename is_base_of_template_impl<base, derived>::type;

template<class T, class ...Ts>
concept ContainIn = tuple_contain<T, Ts...>::value;

template<class T>
concept SystemType = std::is_base_of<ecs::sys::ISystem, T>::value;

template<class T>
concept NumericType = std::is_arithmetic<T>::value;

template<class T>
concept IsUnsigned = std::unsigned_integral<T>;

template<class T>
concept IsSigned = std::signed_integral<T>;

template<class T>
concept IsFPN = std::floating_point<T>;

template<class T>
concept KeyType = requires (T r, T l)
{
    r < l;
};

#pragma region Operator concept

template<class T, class _T>
concept AssignOp = requires (T r, _T l)
{
    r = l;
};

template<class T, class _T>
concept EqOp = requires (T r, _T l)
{
    r == l;
};

template<class T, class _T>
concept NEqOp = requires (T r, _T l)
{
    r != l;
};

template<class T, class _T>
concept LsOp = requires (T r, _T l)
{
    r < l;
};

template<class T, class _T>
concept GtOp = requires (T r, _T l)
{
    r > l;
};

template<class T, class _T>
concept LsEqOp = requires (T r, _T l)
{
    r <= l;
};

template<class T, class _T>
concept GtEqOp = requires (T r, _T l)
{
    r >= l;
};

template<class T, class _T>
concept GlobCompOp = requires (T r, _T l)
{
    r <=> l;
};

template<class T, class _T>
concept AddOp = requires (T r, _T l)
{
    r + l;
};

template<class T, class _T>
concept SubOp = requires (T r, _T l)
{
    r - l;
};

template<class T, class _T>
concept MulOp = requires (T r, _T l)
{
    r * l;
};

template<class T, class _T>
concept DivOp = requires (T r, _T l)
{
    r / l;
};

template<class T, class _T>
concept ModOp = requires (T r, _T l)
{
    r % l;
};

template<class T, class _T>
concept BitAndOp = requires (T r, _T l)
{
    r & l;
};

template<class T, class _T>
concept BitOrOp = requires (T r, _T l)
{
    r | l;
};

template<class T, class _T>
concept BitXorOp = requires (T r, _T l)
{
    r ^ l;
};

template<class T, class _T>
concept LShiftOp = requires (T r, _T l)
{
    r << l;
};

template<class T, class _T>
concept RShiftOp = requires (T r, _T l)
{
    r >> l;
};

template<class T, class _T>
concept AssignAddOp = requires (T r, _T l)
{
    r += l;
};

template<class T, class _T>
concept AssignSubOp = requires (T r, _T l)
{
    r -= l;
};

template<class T, class _T>
concept AssignMulOp = requires (T r, _T l)
{
    r *= l;
};

template<class T, class _T>
concept AssignDivOp = requires (T r, _T l)
{
    r /= l;
};

template<class T, class _T>
concept AssignModOp = requires (T r, _T l)
{
    r %= l;
};

template<class T, class _T>
concept AssignBitAndOp = requires (T r, _T l)
{
    r &= l;
};

template<class T, class _T>
concept AssignBitOrOp = requires (T r, _T l)
{
    r |= l;
};

template<class T, class _T>
concept AssignBitXorOp = requires (T r, _T l)
{
    r ^= l;
};

template<class T, class _T>
concept AssignLShiftOp = requires (T r, _T l)
{
    r <<= l;
};

template<class T, class _T>
concept AssignRShiftOp = requires (T r, _T l)
{
    r >>= l;
};

template<class T>
concept PreIncOp = requires (T r)
{
    r++;
};

template<class T>
concept PostIncOp = requires (T r)
{
    ++r;
};

template<class T>
concept PreDecOp = requires (T r)
{
    r--;
};

template<class T>
concept PostDecOp = requires (T r)
{
    --r;
};

#pragma endregion
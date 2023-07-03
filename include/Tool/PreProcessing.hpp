#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include <optional>
#include <tuple>
#include <type_traits>

// template<class, class>
// struct tuple_prepend;

// template<class T, class ...Ts>
// struct tuple_prepend<T, std::tuple<Ts...>>
// {
//     using type = std::tuple<T, Ts...>;
// };

// template<class ...Ts>
// struct tuple_optional_impl;

// template<class T, class ...Ts>
// struct tuple_optional_impl<T, Ts...>
// {
//     using type = typename tuple_prepend<std::optional<T>, typename tuple_optional_impl<Ts...>::type>::type;
// };

// template<class T>
// struct tuple_optional_impl<T>
// {
//     using type = std::tuple<std::optional<T>>;
// };

// template<class ...Ts>
// struct tuple_optional;

// template<class ...Ts>
// struct tuple_optional<std::tuple<Ts...>>
// {
//     using type = typename tuple_optional_impl<Ts...>::type;
// };

// template<class ...Ts>
// struct tuple_optional<std::tuple<Ts...>>
// {
//     using type = std::tuple<std::optional<Ts>...>;
// };


// template<class ...Ts>
// class Tuple : public tuple_optional<std::tuple<Ts...>>::type
// {
// };

// namespace std
// {
//     template<class T, class ...Ts>
//     std::optional<T> get(Tuple<Ts...> &_tuple) noexcept
//     {
//         return std::get<std::optional<T>>(static_cast<tuple_optional<std::tuple<Ts...>>::type>(*_tuple));
//     }
// }

namespace ecs::sys
{
    class ISystem;
}

namespace eng
{
    template<class ...Ts>
    class Event;
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

template<class T>
concept SystemType = std::is_base_of<ecs::sys::ISystem, T>::value;

template<class T>
concept NumericType = std::is_arithmetic<T>::value;

template<class T>
concept KeyType = requires (T r, T l)
{
    r < l;
};

template<class T>
concept IsEvent = is_base_of_template<eng::Event, T>::value;

#endif
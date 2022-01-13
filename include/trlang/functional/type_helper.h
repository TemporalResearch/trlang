//
// Created by Michael Lynch on 12/01/2022.
//

#pragma once

#include <concepts>

namespace trl
{
    template<class... Types>
    struct TypeList
    {

    };

    template<class HigherOrderType, template <class...> class ExpectedType>
    struct IsExpectedHigherOrderType;

    template<template <class...> class ActualType, template<class...> class ExpectedType, class... Args>
    struct IsExpectedHigherOrderType<ActualType<Args...>, ExpectedType>
    {
        static constexpr bool value = std::is_same_v<ActualType<Args...>, ExpectedType<Args...>>;
    };

    template<class HigherOrderType>
    struct ConvertToTypeList;

    template<template <class...> class HigherOrderType, class... Types>
    struct ConvertToTypeList<HigherOrderType<Types...>>
    {
        using type = TypeList<Types...>;
    };

    namespace internal
    {
        template<class TypeList, class T>
        struct HigherOrderTypeContains
        {
            static constexpr bool value = true;
        };

        template<class T, class X, class... Xs>
        struct HigherOrderTypeContains<TypeList<X, Xs...>, T>
        {
            static constexpr bool value = std::is_same_v<T, X> || HigherOrderTypeContains<TypeList<Xs...>, T>::value;
        };
    }

    template<class Hot, class T>
    struct HigherOrderTypeContains
    {
        static constexpr bool value = trl::internal::HigherOrderTypeContains<ConvertToTypeList<Hot>, T>::value;
    };
}


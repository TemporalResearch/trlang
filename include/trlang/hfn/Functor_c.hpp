//
// Created by Michael Lynch on 13/11/2021.
//

#pragma once

#include <functional>

namespace hfn
{
    template<template <class...> class T, class A, class B, class... Args>
    concept Functor_c = requires (T<Args..., A> a, T<Args..., B> b, std::function<B(A)> f)
    {
        { b = a.map(f) };
    };
}

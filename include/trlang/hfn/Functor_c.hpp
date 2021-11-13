//
// Created by Michael Lynch on 13/11/2021.
//

#pragma once

#include <functional>

namespace hfn
{
    template<template <class> class T, class A, class B>
    concept Functor_c = requires (T<A> a, T<B> b, std::function<B(A)> f)
    {
        { b = a.map(f) };
    };
}

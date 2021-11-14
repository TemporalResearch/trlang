//
// Created by Michael Lynch on 13/11/2021.
//

#pragma once

#include "Functor_c.hpp"
#include <concepts>

namespace hfn
{
    template<template <class...> class T, class A, class B, class... Args>
    concept Applicative_c =
            hfn::Functor_c<T, A, B, Args...>
            && requires (A a, T<Args..., A> aT, T<Args..., B> bT, std::function<B(A)> fn)
            {
                { aT = T<Args..., A>::pure(a) };
                { bT = aT.seqApp(fn) };
            };
}

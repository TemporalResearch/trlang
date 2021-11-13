//
// Created by Michael Lynch on 13/11/2021.
//

#pragma once

#include "Functor_c.hpp"
#include <concepts>

namespace hfn
{
    template<template <class> class T, class A, class B>
    concept Applicative_c =
            hfn::Functor_c<T, A, B>
            && requires (A a, T<A> aT, T<B> bT, std::function<B(A)> fn)
            {
                { aT = T<A>::pure(a) };
                { bT = aT.seqApp(fn) };
            };
}

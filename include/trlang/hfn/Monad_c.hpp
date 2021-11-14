//
// Created by Michael Lynch on 13/11/2021.
//

#pragma once

#include "Applicative_c.hpp"

namespace hfn
{
    template<template <class> class T, class A, class B>
    concept Monad_c =
        Applicative_c<T, A, B>
        && requires (T<A> aT, T<B> bT, std::function<T<B>(A)> fn)
        {
            { bT = aT.flatMap(fn) };
        };
}

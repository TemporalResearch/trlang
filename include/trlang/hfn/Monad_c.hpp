//
// Created by Michael Lynch on 13/11/2021.
//

#pragma once

#include "Applicative_c.hpp"

namespace hfn
{
    template<template <class...> class T, class A, class B, class... Args>
    concept Monad_c =
        Applicative_c<T, A, B, Args...>
        && requires (T<Args..., A> aT, T<Args..., B> bT, std::function<T<Args..., B>(A)> fn)
        {
            { bT = aT.flatMap(fn) };
        };
}

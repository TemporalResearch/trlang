//
// Created by Michael Lynch on 14/11/2021.
//

#pragma once

#include "Monad_c.hpp"

namespace hfn
{
    // (>>) :: forall a b. m a -> m b -> m b
    template<template <class> class T, class A, class B>
            requires Monad_c<T, A, B>
    T<B> seq(T<A> a, T<B> b)
    {
        return a.template flatMap<B>([&b](auto _) {
            return b;
        });
    }
}

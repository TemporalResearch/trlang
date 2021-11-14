//
// Created by Michael Lynch on 14/11/2021.
//

#pragma once

#include "Monad_c.hpp"

namespace hfn
{
    // (>>) :: forall a b. m a -> m b -> m b
    template<template <class...> class T, class A, class B, class... Args>
            requires Monad_c<T, A, B, Args...>
    T<Args..., B> seq(T<Args..., A> a, T<Args..., B> b)
    {
        return a.template flatMap<B>([&b](auto _) {
            return b;
        });
    }

    template<class Function, class... Args>
    struct curry
    {
    public:
        explicit curry(Function fn, Args ...args)
            : fn_(fn)
            , args_(args...)
        { }

        template<class... FinalArgs>
        auto operator ()(FinalArgs &&... finalArgs)
        {
            return std::apply([this, finalArgs...] (auto &&... firstArgs) {
                return fn_(firstArgs..., finalArgs...);
            }, args_);
        }
    private:
        Function fn_;
        std::tuple<Args...> args_;
    };
}

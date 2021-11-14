//
// Created by Michael Lynch on 14/11/2021.
//

#pragma once

#include "Monad_c.hpp"

namespace hfn
{
    /**
     * A monad that does nothing but hold two boxed types
     * @tparam S
     * @tparam T
     */
    template<class S, class T>
    class DoubleBox
    {
    public:

        DoubleBox(S left, T right)
            : leftVal_(left)
            , val_(right)
        { }

        explicit DoubleBox(T right)
            : val_(right)
        {
        }

        [[nodiscard]] const auto &getLeftVal() const { return leftVal_; }
        [[nodiscard]] const auto &getVal() const { return val_; }

        template<class V>
        DoubleBox<S, V> map(std::function<V(T)> fn)
        {
            return DoubleBox<S, V>(leftVal_, fn(val_));
        }


        //Applicative

        static DoubleBox<S, T> pure(T val)
        {
            return DoubleBox<S, T>(val);
        }

        template<class V>
        DoubleBox<S, V> seqApp(std::function<V(T)> fn)
        {
            return map(fn);
        }

        // Monad

        template<class V>
        DoubleBox<S, V> flatMap(std::function<DoubleBox<S, V>(T)> fn)
        {
            return fn(val_);
        }

        bool operator==(const DoubleBox &rhs) const
        {
            return leftVal_ == rhs.leftVal_ &&
                   val_ == rhs.val_;
        }

        bool operator!=(const DoubleBox &rhs) const
        {
            return !(rhs == *this);
        }

    private:
        S leftVal_;
        T val_;
    };
}

static_assert(hfn::Monad_c<hfn::DoubleBox, int, std::string, std::string>);
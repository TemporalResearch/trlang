//
// Created by Michael Lynch on 13/11/2021.
//

#include "Monad_c.hpp"

namespace hfn
{
    /**
     * A monad that does nothing but hold its boxed type
     */
    template <class T>
    class Box
    {
    public:
        explicit Box(T val)
            : val_{val}
        { }

        [[nodiscard]] const auto &getVal() const
        {
            return val_;
        }


        // Functor

        template<class V>
        Box<V> map(std::function<V(T)> fn)
        {
            return Box<V>(fn(val_));
        }


        //Applicative

        static Box<T> pure(T val)
        {
            return Box<T>(val);
        }

        template<class V>
        Box<V> seqApp(std::function<V(T)> fn)
        {
            return map(fn);
        }

        template<class V>
        Box<V> flatMap(std::function<Box<V>(T)> fn)
        {
            return fn(val_);
        }

        friend bool operator==(const Box &lhs, const Box &rhs)
        {
            return lhs.val_ == rhs.val_;
        }

        friend bool operator!=(const Box &lhs, const Box &rhs)
        {
            return !(rhs == lhs);
        }

    private:
        T val_;
    };
}

static_assert(hfn::Monad_c<hfn::Box, int, std::string>);

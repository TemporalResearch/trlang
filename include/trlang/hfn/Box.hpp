//
// Created by Michael Lynch on 13/11/2021.
//

#include "Applicative_c.hpp"

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
    private:
        T val_;
    };
}

static_assert(hfn::Applicative_c<hfn::Box, int, std::string>);

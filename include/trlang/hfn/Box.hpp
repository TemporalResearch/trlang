//
// Created by Michael Lynch on 13/11/2021.
//

#include "Functor_c.hpp"

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

        template<class V>
        Box<V> map(std::function<V(T)> fn)
        {
            return Box<V>(fn(val_));
        }
    private:
        T val_;
    };
}

static_assert(hfn::Functor_c<hfn::Box, int, std::string>);

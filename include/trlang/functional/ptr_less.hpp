//
// Created by Michael Lynch on 02/05/2021.
//

#ifndef TRL_PTR_LESS_HPP
#define TRL_PTR_LESS_HPP

namespace trl
{
    /**
     * Comparitor sorting the underlying object of a pointer with less than.
     */
    template<class T>
    struct ptr_less
    {
        bool operator()(T* a, T* b)
        {
            if (a == nullptr)
            {
                return true;
            }
            return *a < *b;
        }
    };
}

#endif //TRL_PTR_LESS_HPP

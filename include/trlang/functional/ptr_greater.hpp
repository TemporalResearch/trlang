//
// Created by Michael Lynch on 02/05/2021.
//

#ifndef TRL_PTR_GREATER_HPP
#define TRL_PTR_GREATER_HPP

namespace trl
{
    /**
     * Comparitor sorting the underlying object of a pointer with greater than.
     */
    template<class T>
    struct ptr_greater
    {
        bool operator()(T* a, T* b)
        {
            if (a == nullptr)
            {
                return false;
            }
            return *a > *b;
        }
    };
}

#endif //TRL_PTR_GREATER_HPP

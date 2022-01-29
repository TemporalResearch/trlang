#ifndef TEMPORAL_RESEARCH_LANG_TRL_VECTOR_TEMPLATES_HPP
#define TEMPORAL_RESEARCH_LANG_TRL_VECTOR_TEMPLATES_HPP

#include <vector>
#include <concepts>
#include <type_traits>
#include <iostream>

namespace trl::vector::functions::internal
{
    template<class SuperType>
    std::vector<SuperType*>& pushBackOnVector(std::vector<SuperType*>& vect)
    {
        return vect;
    }
    
    template<class SuperType, class X, class... Xs>
        requires std::derived_from<X, SuperType>
    std::vector<SuperType*>& pushBackOnVector(std::vector<SuperType*>& vect, X& first, Xs&... rest)
    {
        vect.push_back(static_cast<SuperType*>(&first));
        return pushBackOnVector(vect, rest...);
    }
}

namespace trl::vector::functions
{
    /**
     * @brief Return's an empty vector of type SuperType*
     * 
     * Provided to allow for no parameter calls to this function.
     * 
     * @tparam SuperType The type of the pointer.
     * @return std::vector<SuperType*> 
     */
    template<class SuperType>
    std::vector<SuperType*> createPolymorphicVector()
    {
        return std::vector<SuperType*>();
    }

    /**
     * @brief Creates a vector of SuperType* containing the provided sub-type objects.
     * 
     * This function is to be used to allow for polymorphism in stack allocated objects.
     * Polymorphism within C++ works with pointers (...what? that's not true), but not references making the use of
     * stack allocated objects in a polymorphic way complicated.
     * 
     * Ownership of the objects pointed to in the vector is not stolen and are never deleted.
     * 
     * @tparam SuperType The supertype of all the provided arguments
     * @tparam X The first argument, must be a sub-type of SuperType
     * @tparam Xs The following arguments, all must be sub-types of SuperType
     * @param first 
     * @param args 
     * @return std::vector<SuperType*> 
     */
    template<class SuperType, class X, class... Xs>
        requires std::derived_from<X, SuperType>
    auto createPolymorphicVector(X&& first, Xs&&... args) -> std::vector<SuperType*>
    {
        std::vector<SuperType*> vect;
        return trl::vector::functions::internal::pushBackOnVector<SuperType, X, Xs...>(vect, first, args...);
    }
}

#endif
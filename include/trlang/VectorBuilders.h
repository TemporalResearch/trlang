//
// Created by Michael Lynch on 29/01/2022.
//

namespace trl
{
    template<class T>
    std::vector<T> combineVectors(std::vector<T> finalVector)
    {
        return finalVector;
    }

    template<class T, std::convertible_to<T> S>
    std::vector<T> combineVectors(std::vector<T> finalVector, const S & nextValue, auto&&... otherVectors)
    {
        finalVector.push_back(nextValue);
        return combineVectors(std::move(finalVector), std::forward<decltype(otherVectors)>(otherVectors)...);
    }

    template<class T, std::convertible_to<T> S>
    std::vector<T> combineVectors(std::vector<T> finalVector, const std::vector<S>& nextVector, auto&&... otherVectors)
    {
        for (const T& value: nextVector)
        {
            finalVector.push_back(value);
        }

        return combineVectors(std::move(finalVector), std::forward<decltype(otherVectors)>(otherVectors)...);
    }

}

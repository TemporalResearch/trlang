//
// Created by Michael Lynch on 30/10/2021.
//

#pragma once

namespace trl::ranges
{
    template<typename T>
    using Iterator_type = decltype(std::begin(std::declval<T>()));

    template<typename T>
    concept Iterable_c = requires(T x, Iterator_type<T> it)
    {
        { it = std::begin(x) };
        { it = std::end(x) };
    };

    template<typename V, typename Functor>
    concept ModifierFunc_c = requires(V val, Functor f)
    {
        std::is_invocable<Functor, V>();
        { f(val) };
    };

    template<typename Functor, typename R, typename... Args>
    concept Function_c = requires (R returnVal, Functor f, Args... args)
    {
        std::is_invocable<Functor, Args...>();
        { returnVal = f(args...) };
    };

    template<Iterable_c T, typename Functor>
    T &forEach(T &iterable, Functor func)
    {
        for (auto &val: iterable) {
            static_assert(ModifierFunc_c<decltype(val), Functor>);
            func(val);
        }

        return iterable;
    }

    template<typename T>
    struct always_false: std::false_type {};

    template<class T, class V>
        requires Iterable_c<T>
    void iterableInsert(T &iterable, const V &value)
    {
        if constexpr(std::is_same<T, std::vector<V>>())
        {
            iterable.push_back(value);
        }
        else
        {
            static_assert(always_false<T>::value, "Unsupported type for iterableInsert");
        }
    }

    template<Iterable_c T, Iterable_c S, class Functor>
    void map(const T &inputMap, S &outputMap, Functor func)
    {
        for (const auto &val: inputMap)
        {
            auto newVal = func(val);
            static_assert(Function_c<Functor, decltype(newVal), decltype(val)>);

            iterableInsert(outputMap, newVal);
        }
    }

}

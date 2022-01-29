//
// Created by Michael Lynch on 29/01/2022.
//

#pragma once

#include <functional>

namespace trl
{
    static inline auto identity = [](const auto &v) {
        return v;
    };

    template<class T>
    auto get_construction_lambda(auto&&... additionalArgs)
    {
        return [&additionalArgs...](auto&& changingArg) {
            return T(
                    std::forward<decltype(changingArg)>(changingArg),
                    std::forward<decltype(additionalArgs)>(additionalArgs)...);
        };
    }

    template<class T>
    auto get_shared_ptr_construction_lambda(auto&&... additionalArgs)
    {
        return [&additionalArgs...](auto&& changingArg) {
            return std::make_shared<T>(
                    std::forward<decltype(changingArg)>(changingArg),
                    std::forward<decltype(additionalArgs)>(additionalArgs)...);
        };
    }
}

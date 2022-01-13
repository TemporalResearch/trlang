//
// Created by Michael Lynch on 12/01/2022.
//

#pragma once

#include <functional>
#include "type_helper.h"
#include <variant>

namespace trl
{
    template<class Variant, class T>
    concept VariantContaining =
            trl::IsExpectedHigherOrderType<Variant, std::variant>::value
            && trl::HigherOrderTypeContains<Variant, T>::value;

    template<class T>
    void visitType(std::function<void(T&)> visitor, VariantContaining<T> auto variant)
    {
        if (T *value = std::get_if<T>(&variant); value != nullptr) visitor(*value);
    }
}

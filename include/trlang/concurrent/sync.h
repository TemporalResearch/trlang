//
// Created by Michael Lynch on 12/01/2022.
//

#pragma once

#include <mutex>

namespace trl
{
    template<class T>
    class sync
    {
    public:
        class accessor
        {
        public:
            accessor(T &value, std::recursive_mutex &m)
                : value_{value}
                , syncronizer_{m}
            {
            }

            T &operator*() { return value_; }
            T *operator->() { return &value_; }
        private:
            T &value_;
            std::unique_lock<std::recursive_mutex> syncronizer_;
        };

        accessor getValue()
        {
            return accessor(value_, lock_);
        }
    private:
        T value_;
        std::recursive_mutex lock_;
    };
}

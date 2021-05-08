//
// Created by Michael Lynch on 08/05/2021.
//

#ifndef AUTO_HARMONY_OPTIONAL_HPP
#define AUTO_HARMONY_OPTIONAL_HPP

#include <optional>

namespace trl
{
    template<class T>
    class optional
    {
    private:
        std::optional<T> _value;
    public:
        optional(const T& value):
            _value(std::make_optional(value))
        {
        }

        optional(const T&& value):
            _value(std::make_optional(value))
        {
        }

        optional(const std::optional<T>& value):
            _value(value)
        {

        }

        optional():
            _value(std::nullopt)
        {
        }

        const T* operator->() const
        {
            return _value.operator->();
        }

        const T& value() const
        {
            return _value.value();
        }

        [[nodiscard]] bool has_value() const
        {
            return _value.has_value();
        }

        template<class U>
        explicit operator U() const
        {
            return static_cast<U>(_value.value());
        }

        template<class U>
        trl::optional<T> operator +(const U& other) const
        {
            if (has_value())
            {
                return optional(_value.value() + other);
            }
            else
            {
                return *this;
            }
        }


        template<class U>
        trl::optional<T> operator -(const U& other) const
        {
            if (has_value())
            {
                return optional(_value.value() - other);
            }
            else
            {
                return *this;
            }
        }

        template<class U>
        trl::optional<T> operator *(const U& other) const
        {
            if (has_value())
            {
                return optional(_value.value() * other);
            }
            else
            {
                return *this;
            }
        }

        template<class U>
        trl::optional<T> operator /(const U& other) const
        {
            if (has_value())
            {
                return optional(_value.value() / other);
            }
            else
            {
                return *this;
            }
        }

        template<class U>
        friend bool operator==(const trl::optional<U>& a, const trl::optional<U>& b)
        {
            if (!(a.has_value() || b.has_value()))
            {
                return true;
            }
            else if (!(a.has_value() && b.has_value()))
            {
                return false;
            }
            else
            {
                return a._value.value() == a._value.value();
            }
        }

        template<class U>
        friend bool operator<(const trl::optional<U>& a, const trl::optional<U>& b)
        {
            if (!(a.has_value() || b.has_value()))
            {
                return false;
            }
            else if (!a.has_value() && b.has_value())
            {
                return true;
            }
            else if (a.has_value() && !b.has_value())
            {
                return false;
            }
            else
            {
                return a._value.value() < b._value.value();
            }
        }

        template<class U>
        friend bool operator>(const trl::optional<U>& a, const trl::optional<U>& b)
        {
            return b < a;
        }

        template<class U>
        friend bool operator<=(const trl::optional<U>& a, const trl::optional<U>& b)
        {
            return !(b < a);
        }

        template<class U>
        friend bool operator>=(const trl::optional<U>& a, const trl::optional<U>& b)
        {
            return !(a < b);
        }
    };
}

#endif //AUTO_HARMONY_OPTIONAL_HPP

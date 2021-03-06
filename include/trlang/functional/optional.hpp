//
// Created by Michael Lynch on 08/05/2021.
//

#ifndef AUTO_HARMONY_OPTIONAL_HPP
#define AUTO_HARMONY_OPTIONAL_HPP

#include <optional>
#include <functional>
#include <stdexcept>

namespace trl
{
    template<class T>
    class optional
    {
    private:
        T* _value;
    public:
        optional(const T& value):
            _value(new T(value))
        {
        }

        optional(const T&& value):
            _value(new T(value))
        {
        }

        optional(const trl::optional<T> & other):
            _value(nullptr)
        {
            if (other.has_value())
            {
                _value = new T(other.value());
            }
        }

        optional(const std::optional<T>& value):
            _value(nullptr)
        {
            if (value.has_value())
            {
                _value = new T(value.value());
            }
        }

        optional():
            _value(nullptr)
        {
        }

        ~optional()
        {
            if (_value != nullptr) delete _value;
            _value = nullptr;
        }

        optional<T> &operator=(const T& value)
        {
            if (_value != nullptr) delete _value;
            _value = new T(value);

            return *this;
        }

        optional<T> &operator=(const optional<T>& otherOpt)
        {
            if (otherOpt.has_value())
            {
                this->operator=(otherOpt.value());
            }
            else
            {
                delete _value;
                _value = nullptr;
            }

            return *this;
        }

        optional<T> &operator=(const std::optional<T> &stdOpt)
        {
            if (stdOpt.has_value())
            {
                this->operator=(stdOpt.value());
            }
            else
            {
                delete _value;
                _value = nullptr;
            }

            return *this;
        }

        const T& value() const
        {
            if (has_value())
            {
                return *_value;
            }
            else
            {
                throw std::runtime_error("trl::optional value was not present");
            }
        }

        [[nodiscard]] bool has_value() const
        {
            return _value != nullptr;
        }

        template<class U>
        trl::optional<U> map(std::function<U(const T&)> fn) const
        {
            if (has_value())
            {
                return trl::optional(fn(*_value));
            }
            else
            {
                return trl::optional<U>();
            }
        }

        template<class U>
        trl::optional<U> flatMap(std::function<trl::optional<U>(const T&)> fn) const
        {
            if (has_value())
            {
                return fn(*_value);
            }
            else
            {
                return trl::optional<U>();
            }
        }

        void forEach(std::function<void(const T&)> fn) const
        {
            if (has_value())
            {
                fn(*_value);
            }
        }

        template<class U>
        explicit operator U() const
        {
            return static_cast<U>(*_value);
        }

        template<class U>
        trl::optional<T> operator +(const U& other) const
        {
            if (has_value())
            {
                return optional((*_value) + other);
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
                return optional((*_value) - other);
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
                return optional((*_value) * other);
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
                return optional((*_value) / other);
            }
            else
            {
                return *this;
            }
        }

        friend bool operator==(const trl::optional<T>& a, const trl::optional<T>& b)
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
                return *(a._value) == *(b._value);
            }
        }

        friend bool operator!=(const trl::optional<T>& a, const trl::optional<T>& b)
        {
            return !(a == b);
        }

        friend bool operator<(const trl::optional<T>& a, const trl::optional<T>& b)
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
                return *(a._value) < *(b._value);
            }
        }

        friend bool operator>(const trl::optional<T>& a, const trl::optional<T>& b)
        {
            return b < a;
        }

        friend bool operator<=(const trl::optional<T>& a, const trl::optional<T>& b)
        {
            return !(b < a);
        }

        friend bool operator>=(const trl::optional<T>& a, const trl::optional<T>& b)
        {
            return !(a < b);
        }
    };
}

#endif //AUTO_HARMONY_OPTIONAL_HPP

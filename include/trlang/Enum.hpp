#ifndef TEMPORAL_RESEARCH_LANG_TRLANG_TYPE_SAFE_ENUM_HPP
#define TEMPORAL_RESEARCH_LANG_TRLANG_TYPE_SAFE_ENUM_HPP

#include <string>

/**
 * @brief Produces an enum with an additional size element with string converting capability.
 * 
 * Using this enum macro will write an enum class in place with a new function `trlang_enumToString` which
 * is able to convert the enum into the string names of the elements.
 * 
 * The enum contains an additional element `size` which when converted to an integer will return the size of the enum.
 * You must not redefine the numbers of the enum.
 * The enum and `trlang_enumToString` will be scoped by the namespace in which the macro is used.
 * 
 */
#define TRLANG_ENUM(name, values...) enum class name {\
        values, \
        size \
    }; \
    template<class T> \
    static const std::string trlang_enumToString(const T& e) \
    { \
        static std::string* enum_names = [] { \
            std::string* nameArray = new std::string[(int)(name::size)]; \
            std::string currentString = #values; \
            int currentPos = 0; \
            for (int i = 0; i < (int)(name::size); i++) \
            { \
                std::string::size_type nextPos = currentString.find(","); \
                nameArray[i] = currentString.substr(currentPos, (nextPos - currentPos)); \
                currentString = currentString.substr(nextPos + 1); \
            } \
            return nameArray; \
        }(); \
        return enum_names[(int)(static_cast<name>(e))]; \
    }; \

#endif
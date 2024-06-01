#pragma once
#include <string>
#include <vector>

class STRING_OPERATION
{
public:
    static std::string MD5(const std::string &Input);
    static std::vector<std::string> SpiltString(const std::string &Input, const std::string &Delimiter);
    template <typename Type>
    static constexpr bool CanConvertToString = std::is_arithmetic_v<Type> ||
                                               (std::is_convertible_v<Type, std::string> && !std::is_null_pointer_v<Type>);
    template <typename Type,
              typename = std::enable_if_t<CanConvertToString<Type>>>
    static std::string ToString(Type Input)
    {
        if constexpr (std::is_arithmetic_v<Type>)
            return std::to_string(Input);
        else
            return std::string(Input);
    }
};

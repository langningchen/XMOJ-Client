#pragma once
#include "API.hpp"

class SET_SETTINGS : public API
{
public:
    class INPUT
    {
    public:
        std::map<std::string, std::string> Settings;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(INPUT, Settings)
    } Input;
    class OUTPUT
    {
    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE_BLANK(OUTPUT)
    } Output;
    using API::API;
    void Call() override;
};
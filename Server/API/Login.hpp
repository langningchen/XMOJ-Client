#pragma once
#include "API.hpp"
class LOGIN : public API
{
public:
    class INPUT
    {
    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE_BLANK(INPUT)
    } Input;
    class OUTPUT
    {
    public:
        bool Success;
        std::string Message;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(OUTPUT, Success, Message)
    } Output;
    using API::API;
    void Call() override;
};
#pragma once
#include "API.hpp"
class GET_SETTINGS : public API
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
        std::string XMOJUsername;
        std::string XMOJPassword;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(OUTPUT, Success, Message, XMOJUsername, XMOJPassword)
    } Output;
    using API::API;
    void Call() override;
};
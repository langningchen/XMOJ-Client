#pragma once
#include "API.hpp"
class SET_SETTINGS : public API
{
public:
    class INPUT
    {
    public:
        std::string XMOJUsername;
        std::string XMOJPassword;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(INPUT, XMOJUsername, XMOJPassword)
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
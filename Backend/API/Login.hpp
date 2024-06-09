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
        NLOHMANN_DEFINE_TYPE_INTRUSIVE_BLANK(OUTPUT)
    } Output;
    using API::API;
    void Call() override;
};
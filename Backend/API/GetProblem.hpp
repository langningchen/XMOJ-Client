#pragma once
#include "API.hpp"
#include <Classes/Problem.hpp>

class GET_PROBLEM : public API
{
public:
    class INPUT
    {
    public:
        int ProblemID;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(INPUT, ProblemID)
    } Input;
    class OUTPUT
    {
    public:
        PROBLEM Problem;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(OUTPUT, Problem)
    } Output;
    using API::API;
    void Call() override;
};
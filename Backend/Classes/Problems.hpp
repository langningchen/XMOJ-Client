#pragma once
#include "Problem.hpp"

class PROBLEMS
{
public:
    static PROBLEM Get(int ID, bool NoCache = false);
    static PROBLEM Get(int ContestID, int ProblemID, bool NoCache = false);
};
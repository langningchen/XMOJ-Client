#include "GetProblem.hpp"
#include <Classes/Problems.hpp>

void GET_PROBLEM::Call()
{
    this->Output.Problem = PROBLEMS::Get(this->Input.ProblemID);
}
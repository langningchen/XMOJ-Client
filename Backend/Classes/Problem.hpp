#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct PROBLEM
{
    struct SAMPLE
    {
        std::string Input;
        std::string Output;
        std::string Description;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(SAMPLE, Input, Output, Description)
    };
    std::string Name;
    std::string InputFilename;
    std::string OutputFilename;
    int TimeLimit;
    int MemoryLimit;
    bool SpecialJudge;
    bool EnableO2;
    int SubmitCount;
    int SolvedCount;
    std::string Description;
    std::string InputFormat;
    std::string OutputFormat;
    std::vector<SAMPLE> Samples;
    std::string DataRange;
    std::string Hint;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PROBLEM, Name, InputFilename, OutputFilename, TimeLimit, MemoryLimit, SpecialJudge, EnableO2, SubmitCount, SolvedCount, Description, InputFormat, OutputFormat, Samples, DataRange, Hint);
};
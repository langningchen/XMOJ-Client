#pragma once
#include <nlohmann/json.hpp>
#include <Database.hpp>
#include <Utilities/WebRequest.hpp>
#include <Classes/XMOJ.hpp>
#include <Utilities/StringOperation.hpp>
#include <Utilities/Logger.hpp>

#define NLOHMANN_DEFINE_TYPE_INTRUSIVE_BLANK(Type)                                       \
    friend void to_json(nlohmann::json &nlohmann_json_j, const Type &nlohmann_json_t) {} \
    friend void from_json(const nlohmann::json &nlohmann_json_j, Type &nlohmann_json_t) {}

class API
{
protected:
    DATABASE *Database;

public:
    API(DATABASE *Database);
    class INPUT;
    class OUTPUT;
    bool Success = false;
    std::string Message;
    virtual void Call() = 0;
};
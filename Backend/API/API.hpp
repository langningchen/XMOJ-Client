#pragma once
#include <Database.hpp>
#include <Utilities/WebRequest.hpp>
#include <Classes/XMOJ.hpp>
#include <Utilities/StringOperation.hpp>
#include <Utilities/Logger.hpp>
#include "APIResult.hpp"

#define NLOHMANN_DEFINE_TYPE_INTRUSIVE_BLANK(Type)                                       \
    friend void to_json(nlohmann::json &nlohmann_json_j, const Type &nlohmann_json_t) {} \
    friend void from_json(const nlohmann::json &nlohmann_json_j, Type &nlohmann_json_t) {}

class API
{
protected:
    DATABASE *Database;
    class INPUT;
    class OUTPUT;

public:
    API(DATABASE *Database);
    virtual void Call() = 0;
};
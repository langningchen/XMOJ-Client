#pragma once
#include <map>
#include <string>
#include <functional>
#include <windows.h>
#include <nlohmann/json.hpp>
#include <Utilities/Database.hpp>

#define DEFINE_API(Name, ClassName) APIFunctions[#Name] = [&]() { \
    ClassName Name(Database);                                     \
    Name.Input = this->APIParams;                                 \
    Name.Call();                                                  \
    APIResults["Data"] = Name.Output;                             \
    APIResults["Success"] = Name.Success;                         \
    APIResults["Message"] = Name.Message;                         \
}

class API_PROCEED
{
private:
    DATABASE *Database;
    std::string APIName;
    nlohmann::json APIParams;
    nlohmann::json APIResults;
    std::map<std::string, std::function<void()>> APIFunctions;

public:
    API_PROCEED(DATABASE *Database, std::string APIName, nlohmann::json &APIParams);
    nlohmann::json Call();
};

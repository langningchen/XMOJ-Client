#pragma once
#include <map>
#include <string>
#include <functional>
#include <nlohmann/json.hpp>
#include <Database.hpp>

#define DEFINE_API(Name, ClassName) APIFunctions[#Name] = [&]() { \
    ClassName Name(Database);                                     \
    Name.Input = APIParams;                                       \
    Name.Call();                                                  \
}

class API_PROCEED
{
private:
    DATABASE *Database;
    std::string APIName;
    nlohmann::json APIParams;
    std::map<std::string, std::function<void()>> APIFunctions;

public:
    API_PROCEED(DATABASE *Database, std::string APIName, nlohmann::json &APIParams);
    nlohmann::json Call();
};

#pragma once
#include <Database.hpp>
#include <functional>
#include <map>
#include <nlohmann/json.hpp>
#include <string>

#define DEFINE_API(Name, ClassName) APIFunctions[#Name] = [&]() { \
    ClassName Name;                                               \
    Name.Input = APIParams;                                       \
    Name.Call();                                                  \
}

class API_PROCEED {
  private:
    std::string APIName;
    nlohmann::json APIParams;
    std::map<std::string, std::function<void()>> APIFunctions;

  public:
    API_PROCEED(std::string APIName, nlohmann::json &APIParams);
    nlohmann::json Call();
};

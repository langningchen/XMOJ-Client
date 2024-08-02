#pragma once
#include <Database.hpp>

class SETTINGS {
  public:
    static std::string Get(std::string Name);
    static std::map<std::string, std::string> GetAll();
    static void Set(std::string Name, std::string Value);
    static bool Has(std::string Name);
};
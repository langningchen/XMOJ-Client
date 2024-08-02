#pragma once
#include "API.hpp"

class GET_SETTINGS : public API {
  public:
    class INPUT {
      public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE_BLANK(INPUT)
    } Input;
    class OUTPUT {
      public:
        std::map<std::string, std::string> Settings;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(OUTPUT, Settings)
    } Output;
    using API::API;
    void Call() override;
};
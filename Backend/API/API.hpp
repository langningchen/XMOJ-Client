#pragma once
#include "APIResult.hpp"
#include <Classes/XMOJ.hpp>
#include <Database.hpp>
#include <Utilities/Logger.hpp>
#include <Utilities/StringOperation.hpp>
#include <Utilities/WebRequest.hpp>

#define NLOHMANN_DEFINE_TYPE_INTRUSIVE_BLANK(Type)                                       \
    friend void to_json(nlohmann::json &nlohmann_json_j, const Type &nlohmann_json_t) {} \
    friend void from_json(const nlohmann::json &nlohmann_json_j, Type &nlohmann_json_t) {}

class API {
  protected:
    class INPUT;
    class OUTPUT;

  public:
    virtual void Call() = 0;
};
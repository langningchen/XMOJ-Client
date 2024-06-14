#include <string>
#include <nlohmann/json.hpp>

class API_RESULT
{
public:
    bool Success;
    std::string Message;
    nlohmann::json Data;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(API_RESULT, Success, Message, Data)
    API_RESULT(bool Success, std::string Message, nlohmann::json Data = {});
};
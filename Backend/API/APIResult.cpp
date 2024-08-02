#include "APIResult.hpp"

API_RESULT::API_RESULT(bool Success, std::string Message, nlohmann::json Data) {
    this->Success = Success;
    this->Message = Message;
    this->Data = Data;
}
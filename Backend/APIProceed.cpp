#include "APIProceed.hpp"
#include "API/GetProblem.hpp"
#include "API/GetSettings.hpp"
#include "API/Login.hpp"
#include "API/SetSettings.hpp"

API_PROCEED::API_PROCEED(std::string APIName, nlohmann::json &APIParams) {
    this->APIName = APIName;
    this->APIParams = APIParams;
    DEFINE_API(Login, LOGIN);
    DEFINE_API(GetSettings, GET_SETTINGS);
    DEFINE_API(SetSettings, SET_SETTINGS);
    DEFINE_API(GetProblem, GET_PROBLEM);
}
nlohmann::json API_PROCEED::Call() {
    if (APIFunctions.find(APIName) == APIFunctions.end())
        return API_RESULT(false, "接口不存在");
    try {
        APIFunctions[APIName]();
        return API_RESULT(false, "接口没有返回结果");
    } catch (const API_RESULT &Result) {
        return Result;
    } catch (const std::exception &e) {
        GeneralLogger.Output(Logger::L_ERROR, "API error: ", e.what());
        return {{"Success", false}, {"Message", "系统后台运行错误"}};
    }
}

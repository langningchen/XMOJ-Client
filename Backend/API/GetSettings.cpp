#include "GetSettings.hpp"
#include <Classes/Settings.hpp>

void GET_SETTINGS::Call() {
    Output.Settings = SETTINGS::GetAll();
    throw API_RESULT(true, "获取设置成功", Output);
}
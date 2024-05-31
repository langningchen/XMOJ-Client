#include "GetSettings.hpp"
#include <Classes/Settings.hpp>

void GET_SETTINGS::Call()
{
    Output.Settings = SETTINGS::GetAll();
    Success = true;
    Message = "获取设置成功";
}
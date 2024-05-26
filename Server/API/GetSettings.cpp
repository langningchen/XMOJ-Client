#include "GetSettings.hpp"
#include <Classes/Settings.hpp>

void GET_SETTINGS::Call()
{
    this->Output.XMOJUsername = SETTINGS::Get("XMOJUsername");
    this->Output.XMOJPassword = SETTINGS::Get("XMOJPassword");
    Output.Success = true;
    Output.Message = "获取设置成功";
}
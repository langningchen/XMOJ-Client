#include "SetSettings.hpp"
#include <Classes/Settings.hpp>

void SET_SETTINGS::Call()
{
    SETTINGS::Set("XMOJUsername", this->Input.XMOJUsername);
    SETTINGS::Set("XMOJPassword", this->Input.XMOJPassword);
    Output.Success = true;
    Output.Message = "修改设置成功";
}
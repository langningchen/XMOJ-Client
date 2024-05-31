#include "SetSettings.hpp"
#include <Classes/Settings.hpp>

void SET_SETTINGS::Call()
{
    for (auto &Setting : Input.Settings)
        SETTINGS::Set(Setting.first, Setting.second);
    Success = true;
    Message = "修改设置成功";
}
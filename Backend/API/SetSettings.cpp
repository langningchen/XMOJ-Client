#include "SetSettings.hpp"
#include <Classes/Settings.hpp>

void SET_SETTINGS::Call() {
    for (auto &Setting : Input.Settings)
        SETTINGS::Set(Setting.first, Setting.second);
    throw API_RESULT(true, "修改设置成功");
}
#include "Login.hpp"
#include <Classes/Settings.hpp>

void LOGIN::Call() {
    std::string UserID = SETTINGS::Get("XMOJUsername");
    std::string Password = STRING_OPERATION::MD5(SETTINGS::Get("XMOJPassword"));
    if (XMOJ::GetLoggedInUsername() == UserID)
        throw API_RESULT(true, "已登录");
    std::string Body = "user_id=" + UserID + "&password=" + Password + "&submit=&csrf=" + XMOJ::GetCSRF();
    std::string Response = WEB_REQUEST().Post(SETTINGS::Get("XMOJBaseURL") + "/login.php")->Body(Body, WEB_REQUEST::FORM)->Send()->AssertResponseCode(200)->GetResponseBody();
    if (Response.find("window.location.href='index.php';") != std::string::npos)
        throw API_RESULT(true, "登录成功");
    else if (Response.find("UserName or Password Wrong!") != std::string::npos)
        throw API_RESULT(false, "用户名或密码错误");
    throw API_RESULT(false, "未知错误：" + Response);
}
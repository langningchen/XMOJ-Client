#include "Login.hpp"
#include <Classes/Settings.hpp>

void LOGIN::Call()
{
    std::string CSRF = XMOJ().GetCSRF();
    std::string UserID = SETTINGS::Get("XMOJUsername");
    std::string Password = STRING_OPERATION::MD5(SETTINGS::Get("XMOJPassword"));
    std::string Body = "user_id=" + UserID + "&password=" + Password + "&submit=&csrf=" + CSRF;
    std::string Response = WEB_REQUEST().Post("https://www.xmoj.tech/login.php")->Body(Body, WEB_REQUEST::FORM)->Send()->AssertResponseCode(200)->GetResponseBody();
    if (Response.find("history.go(-2)") != std::string::npos)
    {
        Success = true;
        Message = "登录成功";
    }
    else if (Response.find("UserName or Password Wrong!") != std::string::npos)
    {
        Message = "用户名或密码错误";
    }
    else
    {
        Message = "未知错误：" + Response;
    }
}
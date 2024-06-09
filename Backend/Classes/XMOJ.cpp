#include "XMOJ.hpp"
#include <Utilities/WebRequest.hpp>
#include <Utilities/Assert.hpp>
#include <Classes/Settings.hpp>

std::string XMOJ::GetCSRF()
{
    std::string HTMLData = WEB_REQUEST().Get(SETTINGS::Get("XMOJBaseURL") + "/csrf.php")->Send()->AssertResponseCode(200)->GetResponseBody();
    size_t Start = ASSERT_DIFFERENT(HTMLData.find("csrf"), std::string::npos) + 13;
    size_t End = ASSERT_DIFFERENT(HTMLData.find("\"", Start), std::string::npos);
    return HTMLData.substr(Start, End - Start);
}

std::string XMOJ::GetLoggedInUsername()
{
    std::string Response = WEB_REQUEST().Get(SETTINGS::Get("XMOJBaseURL") + "/template/bs3/profile.php")->Send()->AssertResponseCode(200)->GetResponseBody();
    size_t Start = ASSERT_DIFFERENT(Response.find("innerHTML"), std::string::npos) + 11;
    size_t End = ASSERT_DIFFERENT(Response.find("\"", Start), std::string::npos);
    std::string Username = Response.substr(Start, End - Start);
    return Username == "登录" ? "" : Username;
}

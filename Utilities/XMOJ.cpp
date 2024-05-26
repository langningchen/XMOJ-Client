#include "XMOJ.hpp"
#include <Utilities/WebRequest.hpp>
#include <Utilities/Assert.hpp>

std::string XMOJ::GetCSRF()
{
    std::string HTMLData = WEB_REQUEST().Get("https://www.xmoj.tech/csrf.php")->Send()->AssertResponseCode(200)->GetResponseBody();
    GeneralLogger.Output(Logger::L_WARNING, HTMLData);
    size_t Start = ASSERT_DIFFERENT(HTMLData.find("csrf"), std::string::npos) + 13;
    size_t End = ASSERT_DIFFERENT(HTMLData.find("\"", Start), std::string::npos);
    return HTMLData.substr(Start, End - Start);
}
#include "WebRequest.hpp"
#include <stdexcept>
#include <Utilities/Assert.hpp>

size_t WEB_REQUEST::WriteCallback(void *Contents, size_t Size, size_t Count, void *UserData)
{
    size_t RealSize = Size * Count;
    ((std::string *)UserData)->append((char *)Contents, RealSize);
    return RealSize;
}
size_t WEB_REQUEST::HeaderCallback(void *Contents, size_t Size, size_t Count, void *UserData)
{
    size_t RealSize = Size * Count;
    ((std::vector<std::string> *)UserData)->push_back(std::string((char *)Contents, RealSize));
    return RealSize;
}
WEB_REQUEST *WEB_REQUEST::Get(std::string URL)
{
    Method = GET;
    this->URL = URL;
    return this;
}
WEB_REQUEST *WEB_REQUEST::Post(std::string URL)
{
    Method = POST;
    this->URL = URL;
    return this;
}
WEB_REQUEST *WEB_REQUEST::Header(std::string Header)
{
    RequestHeaders.push_back(Header);
    return this;
}
WEB_REQUEST *WEB_REQUEST::Header(std::initializer_list<std::string> Headers)
{
    for (auto Header : Headers)
        this->RequestHeaders.push_back(Header);
    return this;
}
WEB_REQUEST *WEB_REQUEST::Body(std::string Body, CONTENT_TYPE ContentType)
{
    RequestBody = Body;
    RequestHeaders.push_back("Content-Type: " + ContentTypes[ContentType]);
    return this;
}
WEB_REQUEST *WEB_REQUEST::Send()
{
    GeneralLogger.Output(Logger::L_DEBUG, "Sending ", (Method == GET ? "GET" : "POST"), " request to ", URL, (RequestBody == "" ? "" : ", with body " + RequestBody));
    Curl = ASSERT_DIFFERENT(curl_easy_init(), nullptr);
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_URL, URL.c_str()));
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_USERAGENT, USER_AGENT.c_str()));
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_WRITEFUNCTION, WriteCallback));
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_WRITEDATA, &ResponseBody));
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_HEADERFUNCTION, HeaderCallback));
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_HEADERDATA, &ResponseHeaders));
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, 0L));
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, 0L));
    ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_FOLLOWLOCATION, 1L));
    if (Method == POST)
    {
        ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_POST, 1L));
        ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, RequestBody.c_str()));
    }
    for (auto Header : RequestHeaders)
        ASSERT_CURL_OK(Curl, curl_easy_setopt(Curl, CURLOPT_HTTPHEADER, curl_slist_append(nullptr, Header.c_str())));
    ASSERT_CURL_OK(Curl, curl_easy_perform(Curl));
    ASSERT_CURL_OK(Curl, curl_easy_getinfo(Curl, CURLINFO_RESPONSE_CODE, &ResponseCode));
    curl_easy_cleanup(Curl);
    GeneralLogger.Output(Logger::L_DEBUG, "Received response code ", ResponseCode, (ResponseBody == "" ? "" : ", with body " + ResponseBody));
    return this;
}
int WEB_REQUEST::GetResponseCode()
{
    return ResponseCode;
}
WEB_REQUEST *WEB_REQUEST::AssertResponseCode(int Code)
{
    ASSERT_SAME(ResponseCode, Code);
    return this;
}
std::string WEB_REQUEST::GetResponseBody()
{
    return ResponseBody;
}

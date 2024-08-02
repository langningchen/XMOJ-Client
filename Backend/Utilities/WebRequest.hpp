#pragma once
#include <Utilities/Assert.hpp>
#include <curl/curl.h>
#include <string>
#include <vector>

class WEB_REQUEST {
  public:
    enum METHOD {
        GET,
        POST
    };
    enum CONTENT_TYPE {
        JSON,
        FORM
    };

  private:
    const std::string USER_AGENT = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3";
    const std::string ContentTypes[2] = {"application/json", "application/x-www-form-urlencoded"};

    METHOD Method;
    std::string URL;
    std::vector<std::string> RequestHeaders;
    std::string RequestBody;
    int ResponseCode;
    std::string ResponseBody;
    std::vector<std::string> ResponseHeaders;

    CURL *Curl;
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static size_t HeaderCallback(void *contents, size_t size, size_t nmemb, void *userp);

  public:
    WEB_REQUEST *Get(std::string URL);
    WEB_REQUEST *Post(std::string URL);
    WEB_REQUEST *Header(std::string Header);
    WEB_REQUEST *Header(std::initializer_list<std::string> Headers);
    WEB_REQUEST *Body(std::string Body, CONTENT_TYPE ContentType);
    WEB_REQUEST *Send();
    int GetResponseCode();
    WEB_REQUEST *AssertResponseCode(int Code);
    std::string GetResponseBody();
};

#include "StringOperation.hpp"
#include <mbedtls/md5.h>

std::string STRING_OPERATION::MD5(const std::string &Input)
{
    mbedtls_md5_context Context;
    mbedtls_md5_starts(&Context);
    mbedtls_md5_update(&Context, (const unsigned char *)Input.c_str(), Input.size());
    unsigned char Output[16];
    mbedtls_md5_finish(&Context, Output);
    mbedtls_md5_free(&Context);
    std::string Result;
    for (int i = 0; i < 16; i++)
        Result += Output[i];
    return Result;
}

std::vector<std::string> STRING_OPERATION::SpiltString(const std::string &Input, const std::string &Delimiter)
{
    std::vector<std::string> Result;
    size_t Start = 0;
    size_t End = Input.find(Delimiter);
    while (End != std::string::npos)
    {
        Result.push_back(Input.substr(Start, End - Start));
        Start = End + Delimiter.size();
        End = Input.find(Delimiter, Start);
    }
    Result.push_back(Input.substr(Start, End));
    return Result;
}

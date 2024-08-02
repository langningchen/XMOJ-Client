#include "StringOperation.hpp"
#include "Assert.hpp"
#include <mbedtls/md5.h>

std::string STRING_OPERATION::MD5(const std::string &Input) {
    mbedtls_md5_context Context;
    mbedtls_md5_starts(&Context);
    mbedtls_md5_update(&Context, reinterpret_cast<const unsigned char *>(Input.c_str()), Input.size());
    unsigned char Output[16];
    mbedtls_md5_finish(&Context, Output);
    std::string Result;
    for (int i = 0; i < 16; i++) {
        char Buffer[3];
        sprintf(Buffer, "%02x", Output[i]);
        Result += Buffer;
    }
    return Result;
}

std::vector<std::string> STRING_OPERATION::SpiltString(const std::string &Input, const std::string &Delimiter) {
    std::vector<std::string> Result;
    size_t Start = 0;
    size_t End = Input.find(Delimiter);
    while (End != std::string::npos) {
        Result.push_back(Input.substr(Start, End - Start));
        Start = End + Delimiter.size();
        End = Input.find(Delimiter, Start);
    }
    Result.push_back(Input.substr(Start, End));
    return Result;
}

std::string STRING_OPERATION::GetMiddle(const std::string &Input, const std::string &Start, const std::string &End, bool AllowEmpty) {
    size_t StartPos = Input.find(Start);
    if (StartPos == std::string::npos) {
        ASSERT_EXPRESSION(AllowEmpty);
        return "";
    }
    StartPos += Start.size();
    size_t EndPos = Input.find(End, StartPos);
    if (EndPos == std::string::npos) {
        ASSERT_EXPRESSION(AllowEmpty);
        return "";
    }
    return Input.substr(StartPos, EndPos - StartPos);
}

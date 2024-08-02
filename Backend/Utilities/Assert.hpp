#pragma once
#include <Utilities/Logger.hpp>
#include <Utilities/StringOperation.hpp>

using namespace std::literals::string_literals;

#ifdef NO_ASSERT

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-value"
#endif

#define ASSERT_EXPRESSION(x) x
#define ASSERT_SAME(x, y) x
#define ASSERT_DIFFERENT(x, y) x
#define ASSERT_CURL_OK(Curl, x) x
#define ASSERT_DATABASE_OK(Database)

#else

#define ASSERT_EXPRESSION(x) ASSERT::Expression(x, #x, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define ASSERT_SAME(x, y) ASSERT::Same(x, y, #x, #y, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define ASSERT_DIFFERENT(x, y) ASSERT::Different(x, y, #x, #y, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define ASSERT_CURL_OK(Curl, x)                                                                                                                       \
    do {                                                                                                                                              \
        auto Result = (x);                                                                                                                            \
        ASSERT::Same(Result, CURLE_OK, (#x + "("s + curl_easy_strerror(Result) + ")"s).c_str(), "CURLE_OK", __FILE__, __LINE__, __PRETTY_FUNCTION__); \
    } while (0)
#define ASSERT_DATABASE_OK(Database)                                                                                                                                                                               \
    do {                                                                                                                                                                                                           \
        auto Result = ((Database).getErrorCode());                                                                                                                                                                 \
        ASSERT::Expression(Result == SQLITE_OK || Result == SQLITE_ROW || Result == SQLITE_DONE, ("Database.getErrorCode()("s + (Database).getErrorMsg() + ")").c_str(), __FILE__, __LINE__, __PRETTY_FUNCTION__); \
    } while (0)

#endif

class ASSERT {
  public:
    static bool Expression(bool Expression, const char *ExpressionString, const char *File, int Line, const char *Function) {
        if (!Expression) {
            GeneralLogger.Output(Logger::L_WARNING, "Assertion failed: ", ExpressionString, "  ", File, ":", Line, " ", Function);
            throw std::runtime_error("Assertion failed");
        }
        return Expression;
    }
    template <typename Type1, typename Type2>
    static Type1 Same(Type1 First, Type2 Second, const char *FirstString, const char *SecondString, const char *File, int Line, const char *Function) {
        if (First != Second) {
            if constexpr (STRING_OPERATION::CanConvertToString<Type1> && STRING_OPERATION::CanConvertToString<Type2>)
                GeneralLogger.Output(Logger::L_WARNING, "Assertion failed: ", FirstString, "(", STRING_OPERATION::ToString(First), ")", " != ", SecondString, "(", STRING_OPERATION::ToString(Second), ")", "  ", File, ":", Line, " ", Function);
            else
                GeneralLogger.Output(Logger::L_WARNING, "Assertion failed: ", FirstString, " != ", SecondString, "  ", File, ":", Line, " ", Function);
            throw std::runtime_error("Assertion failed");
        }
        return First;
    }
    template <typename Type1, typename Type2>
    static Type1 Different(Type1 First, Type2 Second, const char *FirstString, const char *SecondString, const char *File, int Line, const char *Function) {
        if (First == Second) {
            if constexpr (STRING_OPERATION::CanConvertToString<Type1> && STRING_OPERATION::CanConvertToString<Type2>)
                GeneralLogger.Output(Logger::L_WARNING, "Assertion failed: ", FirstString, "(", STRING_OPERATION::ToString(First), ")", " == ", SecondString, "(", STRING_OPERATION::ToString(Second), ")", "  ", File, ":", Line, " ", Function);
            else
                GeneralLogger.Output(Logger::L_WARNING, "Assertion failed: ", FirstString, " == ", SecondString, "  ", File, ":", Line, " ", Function);
            throw std::runtime_error("Assertion failed");
        }
        return First;
    }
};

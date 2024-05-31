#pragma once
#include <iostream>
#include <stdarg.h>
#include <Utilities/StringOperation.hpp>

class Logger
{
public:
    enum LEVEL
    {
        L_DEBUG,
        L_INFO,
        L_WARNING,
        L_ERROR,
        L_CRITICAL
    };

private:
    static inline void Output(std::string Last, LEVEL Level)
    {
        const std::string LevelStrings[5] = {
            "DEBUG",
            "INFO",
            "WARNING",
            "ERROR",
            "CRITICAL"};
        const std::string LevelColors[5] = {
            "\033[0m",
            "\033[34m",
            "\033[33m",
            "\033[31m",
            "\033[1;4;31m"};

        // if (Level == L_DEBUG)
        //     return;

        std::string CurrentTimeString;
        time_t CurrentTime = time(0);
        CurrentTimeString = ctime(&CurrentTime);
        CurrentTimeString.pop_back();
        std::cout << LevelColors[static_cast<int>(Level)]
                  << LevelStrings[static_cast<int>(Level)]
                  << " [" << CurrentTimeString << "]" << ": "
                  << Last << "\033[0m" << std::endl;
        if (Level == L_CRITICAL)
            exit(1);
    }
    template <typename T>
    static inline void Output(std::string Last, LEVEL Level, T Data)
    {
        Last += STRING_OPERATION::ToString(Data);
        Output(Last, Level);
    }
    template <typename T, typename... REST>
    static inline void Output(std::string Last, LEVEL Level, T Data, REST... Rest)
    {
        Last += STRING_OPERATION::ToString(Data);
        Output(Last, Level, Rest...);
    }

public:
    template <typename T,
              typename = std::enable_if_t<STRING_OPERATION::CanConvertToString<T>>>
    static inline void Output(LEVEL Level, T Data)
    {
        Output("", Level, STRING_OPERATION::ToString(Data));
    }
    template <typename T, typename... REST,
              typename = std::enable_if_t<STRING_OPERATION::CanConvertToString<T> &&
                                          (STRING_OPERATION::CanConvertToString<REST> && ...)>>
    static inline void Output(LEVEL Level, T Data, REST... Rest)
    {
        Output("", Level, STRING_OPERATION::ToString(Data), Rest...);
    }
};

extern Logger GeneralLogger;
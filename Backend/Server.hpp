#pragma once
#include <cpp-httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <Database.hpp>

class SERVER
{
public:
    enum STATUS
    {
        STARTED,
        STOPPED
    };

private:
    DATABASE *Database;
    httplib::Server Server;
    STATUS Status;

public:
    SERVER(DATABASE *Database);
    void Start();
    void Stop();
    STATUS GetStatus();
};
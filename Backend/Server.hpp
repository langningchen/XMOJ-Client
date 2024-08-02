#pragma once
#include <Database.hpp>
#include <cpp-httplib/httplib.h>
#include <nlohmann/json.hpp>

class SERVER {
  public:
    enum STATUS {
        STARTED,
        STOPPED
    };

  private:
    httplib::Server Server;
    STATUS Status;

  public:
    SERVER();
    void Start();
    void Stop();
    STATUS GetStatus();
};
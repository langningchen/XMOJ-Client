#include "Server.hpp"
#include "APIProceed.hpp"
#include <Utilities/Logger.hpp>
#include <thread>
#include <Utilities/Assert.hpp>

SERVER::SERVER(DATABASE *Database)
{
    Status = STOPPED;
    this->Database = Database;

    ASSERT_SAME(Server.set_mount_point("/", "HTML"), true);

    Server.set_logger(
              [](const httplib::Request &Request, const httplib::Response &Response)
              {
                  GeneralLogger.Output(Logger::L_DEBUG, Request.remote_addr, ": ", Request.method, " ", Request.path, " --> ", Response.status);
              })
        .Get("/",
             [](const httplib::Request &, httplib::Response &Response)
             {
                 Response.set_redirect("/index.html");
             })
        .Post("/:APIName",
              [&](const httplib::Request &Request, httplib::Response &Response)
              {
                  std::string APIName = Request.path_params.at("APIName");
                  nlohmann::json APIParams;
                  try
                  {
                      APIParams = nlohmann::json::parse(Request.body);
                  }
                  catch (const std::exception &e)
                  {
                      Response.status = 400;
                      Response.set_content(e.what(), "text/plain");
                      return;
                  }
                  try
                  {
                      API_PROCEED APIProceed(Database, APIName, APIParams);
                      nlohmann::json APIResult = APIProceed.Call();
                      GeneralLogger.Output(Logger::L_INFO, "API called: ", APIName, " ", APIParams.dump(), " --> ", APIResult.dump());
                      Response.set_content(APIResult.dump(), "application/json");
                  }
                  catch (const std::exception &e)
                  {
                      Response.status = 500;
                      Response.set_content(e.what(), "text/plain");
                  }
              });
}
void SERVER::Start()
{
    ASSERT_SAME(Status, STOPPED);
    std::thread(
        [&]()
        {
            Server.listen("localhost", 80);
        })
        .detach();
    Status = STARTED;
}
void SERVER::Stop()
{
    ASSERT_SAME(Status, STARTED);
    Server.stop();
    Status = STOPPED;
}
SERVER::STATUS SERVER::GetStatus()
{
    return Status;
}
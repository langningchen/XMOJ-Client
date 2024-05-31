#include <Server.hpp>
#include <Database.hpp>
#include <Utilities/Logger.hpp>

int main()
{
    GeneralLogger.Output(Logger::L_INFO, "Program started");
    DATABASE Database;
    Database.Initialize();
    SERVER Server(&Database);
    Server.Start();
    while (Server.GetStatus() == SERVER::STATUS::STARTED)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    GeneralLogger.Output(Logger::L_INFO, "Program stopped");
    return 0;
}
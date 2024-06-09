#include "Settings.hpp"

std::string SETTINGS::Get(std::string Name)
{
    DATABASE::SQL_DATA SQLData = Database.Select("Settings", {"Value"}, {{"Key", Name}});
    ASSERT_SAME(SQLData.Data.size(), 1u);
    return SQLData.Data[0]["Value"];
}
std::map<std::string, std::string> SETTINGS::GetAll()
{
    std::map<std::string, std::string> Result;
    for (auto &Row : Database.Select("Settings", {"Key", "Value"}).Data)
        Result[Row["Key"]] = std::string(Row["Value"]);
    return Result;
}
void SETTINGS::Set(std::string Name, std::string Value)
{
    if (Database.Select("Settings", {"Value"}, {{"Key", Name}}).Data.size() == 0)
        Database.Insert("Settings", {{"Key", Name}, {"Value", Value}});
    else
        Database.Update("Settings", {{"Value", Value}}, {{"Key", Name}});
}
bool SETTINGS::Has(std::string Name)
{
    return Database.Select("Settings", {"Value"}, {{"Key", Name}}).Data.size();
}

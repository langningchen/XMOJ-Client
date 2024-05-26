#include "Database.hpp"

DATABASE::SQL_DATA::SQL_DATA() {}
DATABASE::SQL_DATA::SQL_DATA(std::initializer_list<std::map<std::string, SQL_DATA_TYPE>> Data)
{
    this->Data = Data;
}
#pragma once
#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>
#include <Utilities/Logger.hpp>
#include <Utilities/Assert.hpp>

class DATABASE
{
public:
    class SQL_DATA
    {
    public:
        class SQL_DATA_TYPE
        {
        public:
            enum DATA_TYPE_ENUM
            {
                INTEGER,
                REAL,
                TEXT,
                BOOLEAN,
                NULL_TYPE
            };

        private:
            DATA_TYPE_ENUM Type;
            int IntegerValue;
            double RealValue;
            std::string TextValue;
            bool BooleanValue;

        public:
            DATA_TYPE_ENUM GetType() const;
            bool IsNull() const;
            operator int() const;
            operator double() const;
            operator std::string() const;
            operator bool() const;
            SQL_DATA_TYPE(int Value);
            SQL_DATA_TYPE(double Value);
            SQL_DATA_TYPE(const char *Value);
            SQL_DATA_TYPE(std::string Value);
            SQL_DATA_TYPE(bool Value);
            SQL_DATA_TYPE(std::nullptr_t Value);
            SQL_DATA_TYPE();
            template <typename T>
            SQL_DATA_TYPE &operator=(T Value)
            {
                *this = SQL_DATA_TYPE(Value);
                return *this;
            }
        };
        std::vector<std::map<std::string, SQL_DATA_TYPE>> Data;
        SQL_DATA();
        SQL_DATA(std::initializer_list<std::map<std::string, SQL_DATA_TYPE>> Data);
    };
    class SQL_META_DATA
    {
    public:
        int InsertID;
        int AffectedRows;
    };
    class SQL_CONDITION
    {
    public:
        std::string Column;
        std::string Operator;
        std::string Value;
        SQL_CONDITION(std::initializer_list<std::string> ConditionData);
    };
    class SQL_ORDER
    {
    public:
        enum SQL_ORDER_TYPE
        {
            ASC,
            DESC
        };
        std::string Column;
        SQL_ORDER_TYPE Order;
        SQL_ORDER(std::string Column);
        SQL_ORDER(std::initializer_list<std::string> OrderData);
    };

private:
    SQLite::Database *Database;

public:
    DATABASE();
    ~DATABASE();
    void Initialize();
    void Execute(std::string Query);
    void Drop(std::string TableName);
    SQL_DATA Select(std::string TableName, std::initializer_list<std::string> Columns,
                    std::initializer_list<SQL_CONDITION> Conditions = {}, std::initializer_list<SQL_ORDER> Orders = {});
    SQL_META_DATA Insert(std::string TableName, std::initializer_list<std::pair<std::string, SQL_DATA::SQL_DATA_TYPE>> Values);
    SQL_META_DATA Update(std::string TableName, std::initializer_list<std::pair<std::string, SQL_DATA::SQL_DATA_TYPE>> Values,
                         std::initializer_list<SQL_CONDITION> Conditions = {});
    SQL_META_DATA Delete(std::string TableName, std::initializer_list<SQL_CONDITION> Conditions);
    std::string GetTableSchema(std::string TableName);
    bool IfTableExists(std::string TableName);
};

extern DATABASE Database;
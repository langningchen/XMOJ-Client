#include "Database.hpp"
#include <algorithm>

DATABASE::DATABASE()
{
    Database = ASSERT_DIFFERENT(new SQLite::Database("Data.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE), nullptr);
    ASSERT_DATABASE_OK(*Database);
}
DATABASE::~DATABASE()
{
    delete Database;
    Database = nullptr;
}
void DATABASE::Initialize()
{
    const std::vector<std::string> Tables = {
        "CREATE TABLE Settings (Key TEXT PRIMARY KEY, Value TEXT)",
        "CREATE TABLE Problems (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, InputFilename TEXT, OutputFilename TEXT, TimeLimit INTEGER, MemoryLimit INTEGER, EnableO2 BOOLEAN, SubmitCount INTEGER, SolvedCount INTEGER, Description TEXT, InputFormat TEXT, OutputFormat TEXT, Samples TEXT, DataRange TEXT, Hint TEXT)",
        "CREATE TABLE Contests (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, StartTime INTEGER, EndTime INTEGER, Problems TEXT, Creator TEXT)",
    };
    for (auto &Table : Tables)
    {
        size_t TableNameStart = ASSERT_DIFFERENT(Table.find("TABLE "), std::string::npos) + 6;
        size_t TableNameEnd = ASSERT_DIFFERENT(Table.find(" ", TableNameStart), std::string::npos);
        std::string TableName = Table.substr(TableNameStart, TableNameEnd - TableNameStart);
        bool TableExists = IfTableExists(TableName);
        std::string TableSchema = TableExists ? GetTableSchema(TableName) : "";
        if (!TableExists || TableSchema != Table)
        {
            GeneralLogger.Output(Logger::L_WARNING, "Table ", TableName, " schema mismatch: ", TableSchema, " != ", Table, ", recreating table");
            if (TableExists)
                Drop(TableName);
            Execute(Table);
        }
        else
            GeneralLogger.Output(Logger::L_DEBUG, "Table ", TableName, " already exists");
    }
}

void DATABASE::Execute(std::string Query, std::vector<std::pair<std::string, SQL_DATA::SQL_DATA_TYPE>> Values, std::function<void(SQLite::Statement *)> Callback)
{
    ASSERT_SAME((size_t)std::count(Query.begin(), Query.end(), '?'), Values.size());
    std::string OutputQuery = Query;
    SQLite::Statement Statement(*Database, Query);
    ASSERT_DATABASE_OK(Statement);
    int Counter = 0;
    for (auto &Value : Values)
    {
        Counter++;
        OutputQuery = OutputQuery.replace(ASSERT_DIFFERENT(OutputQuery.find("?"), std::string::npos), 1, std::string(Value.second));
        switch (Value.second.GetType())
        {
        case SQL_DATA::SQL_DATA_TYPE::INTEGER:
            Statement.bind(Counter, int(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::REAL:
            Statement.bind(Counter, double(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::TEXT:
            Statement.bind(Counter, std::string(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::BOOLEAN:
            Statement.bind(Counter, bool(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::NULL_TYPE:
            Statement.bind(Counter);
            break;
        default:
            ASSERT_EXPRESSION(false);
            break;
        }
        ASSERT_DATABASE_OK(Statement);
    }
    GeneralLogger.Output(Logger::L_DEBUG, "Executing query: ", OutputQuery);
    if (Callback == nullptr)
        Statement.exec();
    else
        while (Statement.executeStep())
        {
            Callback(&Statement);
            ASSERT_DATABASE_OK(Statement);
        }
    ASSERT_DATABASE_OK(Statement);
}
void DATABASE::Drop(std::string TableName)
{
    std::string Query = "DROP TABLE " + TableName;
    GeneralLogger.Output(Logger::L_DEBUG, "Executing query: ", Query);
    SQLite::Statement Statement(*Database, Query);
    ASSERT_DATABASE_OK(Statement);
    Statement.exec();
    ASSERT_DATABASE_OK(Statement);
}
DATABASE::SQL_DATA DATABASE::Select(std::string TableName, std::initializer_list<std::string> Columns,
                                    std::initializer_list<SQL_CONDITION> Conditions, std::initializer_list<SQL_ORDER> Orders)
{
    std::string Query = "SELECT ";
    if (Columns.size() == 0)
        Query += "*";
    else
    {
        for (auto &Column : Columns)
            Query += Column + ", ";
        Query.pop_back();
        Query.pop_back();
    }
    Query += " FROM " + TableName;
    if (Conditions.size() > 0)
    {
        Query += " WHERE ";
        for (auto &Condition : Conditions)
            Query += Condition.Column + " " + Condition.Operator + " ? AND ";
        Query.pop_back();
        Query.pop_back();
        Query.pop_back();
        Query.pop_back();
    }
    if (Orders.size() > 0)
    {
        Query += " ORDER BY ";
        for (auto &Order : Orders)
            Query += Order.Column + " " + (Order.Order == SQL_ORDER::ASC ? "ASC" : "DESC") + ", ";
        Query.pop_back();
        Query.pop_back();
    }
    GeneralLogger.Output(Logger::L_DEBUG, "Executing query: ", Query);
    SQLite::Statement Statement(*Database, Query);
    ASSERT_DATABASE_OK(Statement);
    size_t Counter = 0;
    for (auto &Condition : Conditions)
    {
        Counter++;
        Statement.bind(Counter, Condition.Value);
        ASSERT_DATABASE_OK(Statement);
    }
    SQL_DATA Result;
    while (Statement.executeStep())
    {
        std::map<std::string, DATABASE::SQL_DATA::SQL_DATA_TYPE> Row;
        for (int i = 0; i < Statement.getColumnCount(); i++)
        {
            std::string ColumnName = Statement.getColumnName(i);
            SQLite::Column Column = Statement.getColumn(i);
            switch (Column.getType())
            {
            case SQLITE_INTEGER:
                Row[ColumnName] = Column.getInt();
                break;
            case SQLITE_FLOAT:
                Row[ColumnName] = Column.getDouble();
                break;
            case SQLITE_TEXT:
                Row[ColumnName] = Column.getText();
                break;
            case SQLITE_BLOB:
                Row[ColumnName] = Column.getInt();
                break;
            case SQLITE_NULL:
                Row[ColumnName] = nullptr;
                break;
            default:
                ASSERT_EXPRESSION(false);
                break;
            }
        }
        Result.Data.push_back(Row);
    }
    return Result;
}
DATABASE::SQL_META_DATA DATABASE::Insert(std::string TableName, std::initializer_list<std::pair<std::string, SQL_DATA::SQL_DATA_TYPE>> Values)
{
    std::string Query = "INSERT INTO " + TableName + " (";
    for (auto &Value : Values)
        Query += Value.first + ", ";
    Query.pop_back();
    Query.pop_back();
    Query += ") VALUES (";
    for (size_t i = 0; i < Values.size(); i++)
        Query += "?, ";
    Query.pop_back();
    Query.pop_back();
    Query += ")";
    GeneralLogger.Output(Logger::L_DEBUG, "Executing query: ", Query);
    SQLite::Statement Statement(*Database, Query);
    ASSERT_DATABASE_OK(Statement);
    size_t Counter = 0;
    for (auto &Value : Values)
    {
        Counter++;
        switch (Value.second.GetType())
        {
        case SQL_DATA::SQL_DATA_TYPE::INTEGER:
            Statement.bind(Counter, int(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::REAL:
            Statement.bind(Counter, double(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::TEXT:
            Statement.bind(Counter, std::string(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::BOOLEAN:
            Statement.bind(Counter, bool(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::NULL_TYPE:
            Statement.bind(Counter);
            break;
        default:
            ASSERT_EXPRESSION(false);
            break;
        }
        ASSERT_DATABASE_OK(Statement);
    }
    Statement.exec();
    ASSERT_DATABASE_OK(Statement);
    SQL_META_DATA MetaData;
    MetaData.InsertID = Database->getLastInsertRowid();
    MetaData.AffectedRows = Database->getTotalChanges();
    return MetaData;
}
DATABASE::SQL_META_DATA DATABASE::Update(std::string TableName, std::initializer_list<std::pair<std::string, SQL_DATA::SQL_DATA_TYPE>> Values,
                                         std::initializer_list<SQL_CONDITION> Conditions)
{
    std::string Query = "UPDATE " + TableName + " SET ";
    for (auto &Value : Values)
        Query += Value.first + " = ?, ";
    Query.pop_back();
    Query.pop_back();
    if (Conditions.size() > 0)
    {
        Query += " WHERE ";
        for (auto &Condition : Conditions)
            Query += Condition.Column + " " + Condition.Operator + " ? AND ";
        Query.pop_back();
        Query.pop_back();
        Query.pop_back();
        Query.pop_back();
    }
    GeneralLogger.Output(Logger::L_DEBUG, "Executing query: ", Query);
    SQLite::Statement Statement(*Database, Query);
    ASSERT_DATABASE_OK(Statement);
    size_t Counter = 0;
    for (auto &Value : Values)
    {
        Counter++;
        switch (Value.second.GetType())
        {
        case SQL_DATA::SQL_DATA_TYPE::INTEGER:
            Statement.bind(Counter, int(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::REAL:
            Statement.bind(Counter, double(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::TEXT:
            Statement.bind(Counter, std::string(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::BOOLEAN:
            Statement.bind(Counter, bool(Value.second));
            break;
        case SQL_DATA::SQL_DATA_TYPE::NULL_TYPE:
            Statement.bind(Counter);
            break;
        default:
            ASSERT_EXPRESSION(false);
            break;
        }
        ASSERT_DATABASE_OK(Statement);
    }
    for (auto &Condition : Conditions)
    {
        Counter++;
        Statement.bind(Counter, Condition.Value);
        ASSERT_DATABASE_OK(Statement);
    }
    Statement.exec();
    ASSERT_DATABASE_OK(Statement);
    SQL_META_DATA MetaData;
    MetaData.AffectedRows = Database->getTotalChanges();
    return MetaData;
}
DATABASE::SQL_META_DATA DATABASE::Delete(std::string TableName, std::initializer_list<SQL_CONDITION> Conditions)
{
    std::string Query = "DELETE FROM " + TableName;
    if (Conditions.size() > 0)
    {
        Query += " WHERE ";
        for (auto &Condition : Conditions)
            Query += Condition.Column + " " + Condition.Operator + " ? AND ";
        Query.pop_back();
        Query.pop_back();
        Query.pop_back();
        Query.pop_back();
    }
    GeneralLogger.Output(Logger::L_DEBUG, "Executing query: ", Query);
    SQLite::Statement Statement(*Database, Query);
    ASSERT_DATABASE_OK(Statement);
    size_t Counter = 0;
    for (auto &Condition : Conditions)
    {
        Counter++;
        Statement.bind(Counter, Condition.Value);
        ASSERT_DATABASE_OK(Statement);
    }
    Statement.exec();
    ASSERT_DATABASE_OK(Statement);
    SQL_META_DATA MetaData;
    MetaData.AffectedRows = Database->getTotalChanges();
    return MetaData;
}
std::string DATABASE::GetTableSchema(std::string TableName)
{
    SQL_DATA MasterData = Select("sqlite_master", {}, {{"type", "table"}, {"name", TableName}});
    ASSERT_SAME(MasterData.Data.size(), 1u);
    return MasterData.Data[0]["sql"];
}
bool DATABASE::IfTableExists(std::string TableName)
{
    SQL_DATA MasterData = Select("sqlite_master", {}, {{"type", "table"}, {"name", TableName}});
    return MasterData.Data.size() > 0;
}

DATABASE Database;

#include "Database.hpp"

DATABASE::SQL_DATA::SQL_DATA_TYPE::DATA_TYPE_ENUM DATABASE::SQL_DATA::SQL_DATA_TYPE::GetType() const
{
    return Type;
}
bool DATABASE::SQL_DATA::SQL_DATA_TYPE::IsNull() const
{
    return Type == NULL_TYPE;
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::operator int() const
{
    switch (Type)
    {
    case INTEGER:
        return IntegerValue;
    case REAL:
        GeneralLogger.Output(Logger::L_WARNING, "Converting REAL to INTEGER");
        return RealValue;
    case TEXT:
        GeneralLogger.Output(Logger::L_WARNING, "Converting TEXT to INTEGER");
        return std::stoi(TextValue);
    case BOOLEAN:
        GeneralLogger.Output(Logger::L_WARNING, "Converting BOOLEAN to INTEGER");
        return BooleanValue;
    case NULL_TYPE:
        GeneralLogger.Output(Logger::L_WARNING, "Converting NULL to INTEGER");
        return 0;
    default:
        ASSERT_EXPRESSION(false);
        return 0;
    }
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::operator double() const
{
    switch (Type)
    {
    case INTEGER:
        GeneralLogger.Output(Logger::L_WARNING, "Converting INTEGER to REAL");
        return IntegerValue;
    case REAL:
        return RealValue;
    case TEXT:
        GeneralLogger.Output(Logger::L_WARNING, "Converting TEXT to REAL");
        return std::stod(TextValue);
    case BOOLEAN:
        GeneralLogger.Output(Logger::L_WARNING, "Converting BOOLEAN to REAL");
        return BooleanValue;
    case NULL_TYPE:
        GeneralLogger.Output(Logger::L_WARNING, "Converting NULL to REAL");
        return 0;
        break;
    default:
        ASSERT_EXPRESSION(false);
        return 0;
    }
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::operator std::string() const
{
    switch (Type)
    {
    case INTEGER:
        GeneralLogger.Output(Logger::L_WARNING, "Converting INTEGER to TEXT");
        return std::to_string(IntegerValue);
    case REAL:
        GeneralLogger.Output(Logger::L_WARNING, "Converting REAL to TEXT");
        return std::to_string(RealValue);
    case TEXT:
        return TextValue;
    case BOOLEAN:
        GeneralLogger.Output(Logger::L_WARNING, "Converting BOOLEAN to TEXT");
        return BooleanValue ? "true" : "false";
    case NULL_TYPE:
        GeneralLogger.Output(Logger::L_WARNING, "Converting NULL to TEXT");
        return "NULL";
    default:
        ASSERT_EXPRESSION(false);
        return "";
    }
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::operator bool() const
{
    switch (Type)
    {
    case INTEGER:
        GeneralLogger.Output(Logger::L_WARNING, "Converting INTEGER to BOOLEAN");
        return IntegerValue;
    case REAL:
        GeneralLogger.Output(Logger::L_WARNING, "Converting REAL to BOOLEAN");
        return RealValue;
    case TEXT:
        GeneralLogger.Output(Logger::L_WARNING, "Converting TEXT to BOOLEAN");
        ASSERT_EXPRESSION(TextValue == "true" || TextValue == "false");
        return TextValue == "true";
    case BOOLEAN:
        return BooleanValue;
    case NULL_TYPE:
        GeneralLogger.Output(Logger::L_WARNING, "Converting NULL to BOOLEAN");
        return false;
        break;
    default:
        ASSERT_EXPRESSION(false);
        return false;
    }
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::SQL_DATA_TYPE(int Value) : Type(INTEGER)
{
    this->IntegerValue = Value;
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::SQL_DATA_TYPE(double Value) : Type(REAL)
{
    this->RealValue = Value;
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::SQL_DATA_TYPE(const char *Value) : Type(TEXT)
{
    this->TextValue = Value;
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::SQL_DATA_TYPE(std::string Value) : Type(TEXT)
{
    this->TextValue = Value;
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::SQL_DATA_TYPE(bool Value) : Type(BOOLEAN)
{
    this->BooleanValue = Value;
}
DATABASE::SQL_DATA::SQL_DATA_TYPE::SQL_DATA_TYPE(std::nullptr_t Value) : Type(NULL_TYPE) {}
DATABASE::SQL_DATA::SQL_DATA_TYPE::SQL_DATA_TYPE() : Type(NULL_TYPE) {}
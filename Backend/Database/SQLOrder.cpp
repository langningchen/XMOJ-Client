#include "Database.hpp"

DATABASE::SQL_ORDER::SQL_ORDER(std::string Column)
{
    this->Column = Column;
    Order = ASC;
}
DATABASE::SQL_ORDER::SQL_ORDER(std::initializer_list<std::string> OrderData)
{
    ASSERT_SAME(OrderData.size(), 2u);
    Column = *OrderData.begin();
    std::string OrderString = *(OrderData.begin() + 1);
    ASSERT_EXPRESSION(OrderString == "ASC" || OrderString == "DESC");
    Order = OrderString == "ASC" ? ASC : DESC;
}
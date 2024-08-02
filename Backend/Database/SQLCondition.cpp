#include "Database.hpp"

DATABASE::SQL_CONDITION::SQL_CONDITION(std::initializer_list<std::string> ConditionData) {
    ASSERT_EXPRESSION(ConditionData.size() == 2 || ConditionData.size() == 3);
    if (ConditionData.size() == 3) {
        Column = *ConditionData.begin();
        Operator = *(ConditionData.begin() + 1);
        Value = *(ConditionData.begin() + 2);
    } else if (ConditionData.size() == 2) {
        Column = *ConditionData.begin();
        Operator = "=";
        Value = *(ConditionData.begin() + 1);
    }
}
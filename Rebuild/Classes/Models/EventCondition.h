#ifndef EVENT_CONDITION_H 
#define EVENT_CONDITION_H

#include <string>

enum class CondComparitor {
    LT, GT, EQ, LTEQ, GTEQ
};

struct EventCondition {
    std::string key;     
    CondComparitor comparitor;
    int value;
};

#endif
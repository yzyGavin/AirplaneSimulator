//
// Created by ofir8 on 12/20/18.
//

#include "ConditionCommand.h"

bool ConditionCommand::isTrue() {
    vector<string>::iterator it = params.begin();
    Expression* left = ExpressionBuilder::getExpression(it, params.end());
    string sign = *it;
    if (*it == ">" || *it == "<") {
        it = it + 1;
    } else if (*it == ">=" || *it == "<=" || *it == "==" || *it == "!=") {
        it = it + 1;
    } else {
        cout << "wrong input" << endl;
        return false;
    }
    Expression* right = ExpressionBuilder::getExpression(it, params.end());
    if (it != params.end()) {
        //we have unused word
        cout << "wrong input" << endl;
        return false;
    }
    if (sign == ">" && (left->calculate() > right->calculate())) {
        return true;
    }
    if (sign == "<" && (left->calculate() < right->calculate())) {
        return true;
    }
    if (sign == ">=" && (left->calculate() >= right->calculate())) {
        return true;
    }
    if (sign == "<=" && (left->calculate() <= right->calculate())) {
        return true;
    }
    if (sign == "==" && (left->calculate() == right->calculate())) {
        return true;
    }
    if (sign == "!=" && (left->calculate() != right->calculate())) {
        return true;
    }
    return false;
}
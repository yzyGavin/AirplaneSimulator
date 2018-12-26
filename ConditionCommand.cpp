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
    double leftEx = left->calculate();
    double rightEx = right->calculate();
    delete left;
    delete right;
    if (it != params.end()) {
        //we have unused word
        cout << "wrong input" << endl;
        return false;
    }
    if (sign == ">" && (leftEx > rightEx)) {
        return true;
    }
    if (sign == "<" && (leftEx < rightEx)) {
        return true;
    }
    if (sign == ">=" && (leftEx >= rightEx)) {
        return true;
    }
    if (sign == "<=" && (leftEx <= rightEx)) {
        return true;
    }
    if (sign == "==" && (leftEx == rightEx)) {
        return true;
    }
    if (sign == "!=" && (leftEx != rightEx)) {
        return true;
    }
    return false;
}
//
// Created by ofir8 on 12/20/18.
//

#include "ConditionCommand.h"

bool ConditionCommand::isTrue() {
    vector<string>::iterator it = params.begin();
    //Get the fisrt Expression
    Expression* left = ExpressionBuilder::getExpression(it, params.end());
    string sign = *it;
    //Check there is a sign
    if (*it == ">" || *it == "<") {
        it = it + 1;
    } else if (*it == ">=" || *it == "<=" || *it == "==" || *it == "!=") {
        it = it + 1;
    } else {
        // if the condition is not with the right suntax
        cout << "wrong input" << endl;
        return false;
    }
    //Get the second Expression
    Expression* right = ExpressionBuilder::getExpression(it, params.end());
    //save the values and delete the info from the heap
    double leftEx = left->calculate();
    double rightEx = right->calculate();
    delete left;
    delete right;
    if (it != params.end()) {
        //we have unused word
        cout << "wrong input" << endl;
        return false;
    }
    //Check the condition by the sign
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
//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_COMMAND_H
#define PROJECTDEMO_COMMAND_H

#include "vector"
#include "string"
#include "Expression.h"
#include "iostream"
#include "ExpressionBuilder.h"

using namespace std;

class Command {
public:
    virtual void doCommand() = 0;
    virtual ~Command(){}
};

#endif //PROJECTDEMO_COMMAND_H

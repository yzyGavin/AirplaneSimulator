//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_COMMANDFACTORY_H
#define PROJECTDEMO_COMMANDFACTORY_H

#include <vector>
#include "Command.h"
#include "string"
#include "CommandExpression.h"
using namespace std;

class CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) = 0;
};

#endif //PROJECTDEMO_COMMANDFACTORY_H

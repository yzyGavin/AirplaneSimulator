//
// Created by zomry1 on 23/12/18.
//

#ifndef PROJECTDEMO_ENTERCFACTORY_H
#define PROJECTDEMO_ENTERCFACTORY_H

#include "CommandFactory.h"
#include "EnterCCommand.h"

class EnterCFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new EnterCCommand(params));
    }
};

#endif //PROJECTDEMO_ENTERCFACTORY_H

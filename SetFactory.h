//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_SETFACTORY_H
#define PROJECTDEMO_SETFACTORY_H

#include "CommandFactory.h"
#include "SetCommand.h"

class SetFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new SetCommand(params));
    }
};

#endif //PROJECTDEMO_SETFACTORY_H

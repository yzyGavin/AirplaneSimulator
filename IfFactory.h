//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_IFFACTORY_H
#define PROJECTDEMO_IFFACTORY_H

#include "CommandFactory.h"
#include "IfCommand.h"

class IfFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new IfCommand(params, commands));
    }
};

#endif //PROJECTDEMO_IFFACTORY_H

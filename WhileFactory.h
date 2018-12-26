//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_WHILEFACTORY_H
#define PROJECTDEMO_WHILEFACTORY_H

#include "CommandFactory.h"
#include "LoopCommand.h"

class WhileFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new LoopCommand(params, commands));
    }
};

#endif //PROJECTDEMO_WHILEFACTORY_H

//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_PRINTFACTORY_H
#define PROJECTDEMO_PRINTFACTORY_H

#include "CommandFactory.h"
#include "PrintCommand.h"

class PrintFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new PrintCommand(params));
    }
};

#endif //PROJECTDEMO_PRINTFACTORY_H

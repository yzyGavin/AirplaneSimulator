//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_VARFACTORY_H
#define PROJECTDEMO_VARFACTORY_H

#include "CommandFactory.h"
#include "VarCommand.h"

class VarFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new VarCommand(params));
    }
};

#endif //PROJECTDEMO_VARFACTORY_H

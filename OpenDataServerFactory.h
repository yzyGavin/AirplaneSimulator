//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_OPENDATASERVERFACTORY_H
#define PROJECTDEMO_OPENDATASERVERFACTORY_H

#include "CommandFactory.h"
#include "OpenDataServerCommand.h"

class OpenDataServerFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new OpenDataServerCommand(params));
    }
};

#endif //PROJECTDEMO_OPENDATASERVERFACTORY_H

//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_CONNECTFACTORY_H
#define PROJECTDEMO_CONNECTFACTORY_H

#include "CommandFactory.h"
#include "ConnectToServerCommand.h"

class ConnectFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new ConnectToServerCommand(params));
    }
};

#endif //PROJECTDEMO_CONNECTFACTORY_H

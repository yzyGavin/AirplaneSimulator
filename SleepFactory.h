//
// Created by zomry1 on 25/12/18.
//

#ifndef PROJECTDEMO_SLEEPFACTORY_H
#define PROJECTDEMO_SLEEPFACTORY_H

#include "CommandFactory.h"
#include "SleepCommand.h"

class SleepFactory : public CommandFactory {
public:
    virtual Expression* getCommand(const vector<string> &params, const vector<Expression*> &commands) {
        return new CommandExpression(new SleepCommand(params));
    }
};

#endif //PROJECTDEMO_SLEEPFACTORY_H

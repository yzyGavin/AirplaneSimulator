//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_LOOPCOMMAND_H
#define PROJECTDEMO_LOOPCOMMAND_H

#include "ConditionCommand.h"

class LoopCommand : public ConditionCommand {
    vector<Expression*> commands;
public:
    LoopCommand(vector<string> vec, vector<Expression*> commandsList) : ConditionCommand(vec) {
        commands = commandsList;
    }
    virtual void doCommand();
    ~LoopCommand();
};

#endif //PROJECTDEMO_LOOPCOMMAND_H

//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_IFCOMMAND_H
#define PROJECTDEMO_IFCOMMAND_H

#include "ConditionCommand.h"

class IfCommand : public ConditionCommand {
    vector<Expression*> commands;
public:
    IfCommand(vector<string> vec, vector<Expression*> commandsList) : ConditionCommand(vec) {
        commands = commandsList;
    }
    virtual void doCommand();
    ~IfCommand();
};

#endif //PROJECTDEMO_IFCOMMAND_H

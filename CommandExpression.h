//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_COMMANDEXPRESSION_H
#define PROJECTDEMO_COMMANDEXPRESSION_H

#include "Expression.h"
#include "Command.h"

class CommandExpression : public Expression {
    Command* command;
public:
    CommandExpression(Command* c) {
        command = c;
    }
    double calculate() {
        command->doCommand();
        return 0;
    }
    ~CommandExpression() {
        delete(command);
    }
};

#endif //PROJECTDEMO_COMMANDEXPRESSION_H

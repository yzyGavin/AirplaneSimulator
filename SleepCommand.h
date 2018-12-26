//
// Created by zomry1 on 25/12/18.
//

#ifndef PROJECTDEMO_SLEEPCOMMAND_H
#define PROJECTDEMO_SLEEPCOMMAND_H

#include <unistd.h>
#include "Command.h"

class SleepCommand: public Command {
    vector<string> params;
public:
    SleepCommand(vector<string> params) {
        this->params = params;
    }
    /**
     * the method makes the program to sleep for the asked time
     */
    void doCommand() {
        vector<string>::iterator start = params.begin();
        vector<string>::iterator end = params.end();
        Expression* ex = ExpressionBuilder::getExpression(start,end);
        sleep(ex->calculate() / 1000);
        delete(ex);};

    ~SleepCommand(){}
};
#endif //PROJECTDEMO_SLEEPCOMMAND_H

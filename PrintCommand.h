//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_PRINTCOMMAND_H
#define PROJECTDEMO_PRINTCOMMAND_H


#include "Command.h"

class PrintCommand : public Command{
    vector<string> params;

public:
    PrintCommand(vector<string> params) {
        this->params = params;
    }

    virtual void doCommand();

    ~PrintCommand(){}
};


#endif //PROJECTDEMO_PRINTCOMMAND_H

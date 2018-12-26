//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_VARCOMMAND_H
#define PROJECTDEMO_VARCOMMAND_H

#include "Command.h"
#include "MapsHandler.h"

class VarCommand : public Command {
    vector<string> params;

public:
    VarCommand(vector<string> params) {
        this->params = params;
    }

    virtual void doCommand();

    ~VarCommand(){}
};

#endif //PROJECTDEMO_VARCOMMAND_H

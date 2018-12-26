//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_OPENDATASERVERCOMMAND_H
#define PROJECTDEMO_OPENDATASERVERCOMMAND_H

#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "Command.h"
#include "MapsHandler.h"

class OpenDataServerCommand : public Command {
    vector<string> params;

public:
    OpenDataServerCommand (vector<string> params) {
        this->params = params;
    }
    void doCommand();

    ~OpenDataServerCommand(){}
};

#endif //PROJECTDEMO_OPENDATASERVERCOMMAND_H

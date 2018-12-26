//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_CONNECTTOSERVERCOMMAND_H
#define PROJECTDEMO_CONNECTTOSERVERCOMMAND_H

#include "Command.h"
#include "ComunicateWithSimulator.h"

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>

class ConnectToServerCommand : public Command {
    vector<string> params;
public:
    ConnectToServerCommand(vector<string> params) {
        this->params = params;
    }
    virtual void doCommand();

    ~ConnectToServerCommand(){}
};

#endif //PROJECTDEMO_CONNECTTOSERVERCOMMAND_H

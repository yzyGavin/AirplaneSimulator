//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_SETCOMMAND_H
#define PROJECTDEMO_SETCOMMAND_H

#include "Command.h"

class SetCommand: public Command {
    string var;
    string sign;
    vector<string> params;
public:
    SetCommand(vector<string> vec);
    void doCommand();

    ~SetCommand(){}
};

#endif //PROJECTDEMO_SETCOMMAND_H

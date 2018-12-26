//
// Created by zomry1 on 23/12/18.
//

#ifndef PROJECTDEMO_ENTERCCOMMAND_H
#define PROJECTDEMO_ENTERCCOMMAND_H

#include "Command.h"

class EnterCCommand : public Command{

public:
    EnterCCommand(vector<string> params) {
    }

    virtual void doCommand() {
        string nothing;
        getline(cin, nothing);};
};


#endif //PROJECTDEMO_ENTERCCOMMAND_H

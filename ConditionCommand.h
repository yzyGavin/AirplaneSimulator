//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_CONDITIONCOMMAND_H
#define PROJECTDEMO_CONDITIONCOMMAND_H

#include "Command.h"

class ConditionCommand : public Command {
    vector<string> params;
public:
    ConditionCommand (vector<string> vec) {
        params = vec;
    }

protected:
    bool isTrue();
};

#endif //PROJECTDEMO_CONDITIONCOMMAND_H

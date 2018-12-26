//
// Created by ofir8 on 12/19/18.
//

#ifndef PROJECTDEMO_VAR_H
#define PROJECTDEMO_VAR_H

#include "Expression.h"
#include "MapsHandler.h"

class Var : public Expression {
string var;
public:
    Var(string st) {
        var = st;
    }
    virtual double calculate() {
        return MapsHandler::getVarValue(var);
    }
};

#endif //PROJECTDEMO_VAR_H

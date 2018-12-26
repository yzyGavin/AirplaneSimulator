//
// Created by ofir8 on 12/19/18.
//

#ifndef PROJECTDEMO_EXPRESSION_H
#define PROJECTDEMO_EXPRESSION_H

#include <string>
using namespace std;

class Expression {
public:
    virtual double calculate() = 0;
    virtual ~Expression(){}
};

#endif //PROJECTDEMO_EXPRESSION_H

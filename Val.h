//
// Created by ofir8 on 12/19/18.
//

#ifndef PROJECTDEMO_VAL_H
#define PROJECTDEMO_VAL_H

#import "Expression.h"

class Val : public Expression {
    double val;
public:
    Val(double num) {
        val = num;
    }
    virtual double calculate() {
        return val;
    }
};


#endif //PROJECTDEMO_VAL_H

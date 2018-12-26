//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_MUL_H
#define PROJECTDEMO_MUL_H

#include "Expression.h"

class Mul : public Expression {
    Expression* right;
    Expression* left;
public:
    Mul(Expression* left, Expression* right) {
        this->right = right;
        this->left = left;
    }

    virtual double calculate() {
        return left->calculate() * right->calculate();
    }
    /**
     * delete - allocate memory
     */
    ~Mul() {
        delete (left);
        delete(right);
    }
};

#endif //PROJECTDEMO_MUL_H

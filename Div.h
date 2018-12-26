//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_DIV_H
#define PROJECTDEMO_DIV_H

#include "Expression.h"

class Div : public Expression {
    Expression* right;
    Expression* left;
public:
    Div(Expression* left, Expression* right) {
        this->right = right;
        this->left = left;
    }
    virtual double calculate() {
        return left->calculate() / right->calculate();
    }
    /**
     * the distructor deletes the members- allocated memory heap
     */
    ~Div() {
        delete (left);
        delete(right);
    }
};

#endif //PROJECTDEMO_DIV_H

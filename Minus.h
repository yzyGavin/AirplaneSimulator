//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_MINUS_H
#define PROJECTDEMO_MINUS_H

#include "Expression.h"

class Minus : public  Expression {
    Expression* right;
    Expression* left;
public:
    Minus(Expression* left, Expression* right) {
        this->right = right;
        this->left = left;
    }
    virtual double calculate() {
        return left->calculate() - right->calculate();
    }
    /**
     * delete - allocate memory
     */
    ~Minus() {
        delete (left);
        delete(right);
    }
};

#endif //PROJECTDEMO_MINUS_H

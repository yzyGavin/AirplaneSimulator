//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_PLUS_H
#define PROJECTDEMO_PLUS_H

#include "Expression.h"

class Plus : public Expression {
    Expression* right;
    Expression* left;
public:
    Plus(Expression* left, Expression* right) {
        this->right = right;
        this->left = left;
    }
    virtual double calculate() {
        return left->calculate() + right->calculate();
    }
    /**
     * delete - allocate memory
     */
    ~Plus() {
        delete (left);
        delete(right);
    }
};


#endif //PROJECTDEMO_PLUS_H

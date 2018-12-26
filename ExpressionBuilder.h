//
// Created by ofir8 on 12/20/18.
//

#ifndef PROJECTDEMO_EXPRESSIONBUILDER_H
#define PROJECTDEMO_EXPRESSIONBUILDER_H

#include <vector>
#include "Expression.h"

class ExpressionBuilder  {
public:
    static Expression* getExpression (vector<string>::iterator &it, vector<string>::iterator end);
};


#endif //PROJECTDEMO_EXPRESSIONBUILDER_H

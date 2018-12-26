//
// Created by ofir8 on 12/20/18.
//

#include "ExpressionBuilder.h"
#include "Val.h"
#include "Var.h"
#include "Div.h"
#include "Mul.h"
#include "Minus.h"
#include "Plus.h"

#include <iostream>
#include <stack>
#include <queue>
#include <iterator>
#include <vector>
#include <string>

using namespace std;
void checkNegative(vector<string> &expressions) {
    //Two cases for negative number , at the beginning of the strings, or after (
    if(expressions[0] == "-") {
        //Maybe need to add the position
        expressions.insert(expressions.begin(),"0");
    }
    bool lastBracket = false;
    bool lastOperator = false;
    vector<string>::iterator next;
    for(vector<string>::iterator it = expressions.begin(); it != expressions.end(); it++ ) {
        //If we didnt have a ( before
        if(!lastBracket) {
            if (*it == "(") {
                lastBracket = true;
                lastOperator = false;
                continue;
            }
        }

        if(!lastOperator) {
            if(*it == "*" || *it == "+" || *it == "/") {
                lastOperator = true;
                lastBracket = false;
                continue;
            }
        }
        if(lastBracket && *it == "-") {
            it = expressions.insert(it,"0");
            it++;
        }
        if(lastOperator && *it == "-") {
            //Curr we on the -: it-1 is before the -
            next = expressions.insert(it-1, "(");
            //next is on the ( : next+1 is after the (
            next = expressions.insert(next+1, "0");
            //next is on the ( : next+ is after the - and the number
            next = expressions.insert(next+2, ")");
        }
        lastBracket = false;
        lastOperator = false;
    }
}

queue<string> shuntingYard(vector<string> objects) {
    stack <string> st;
    queue <string> qu;
    for(vector<string>::iterator it = objects.begin(); it != objects.end(); it++) {
        if (*it == "+" || *it == "-" ) {
            //They have a greater precendence
            while(!st.empty() && (st.top() == "/" || st.top() == "*")) {
                qu.emplace(st.top());
                st.pop();
            }
            st.push(*it);
        }
        else if (*it == "/" || *it == "*" || *it == "(") {
            st.push(*it);
        }
        else if (*it == ")") {
            while (st.top() != "(") {
                qu.emplace(st.top());
                st.pop();
            }
            //To remove the )
            st.pop();
        }
        else {
            //Is a numebr
            qu.emplace(*it);
        }
    }
    //After finish to read all the expressions
    while(!st.empty()) {
        qu.emplace(st.top());
        st.pop();
    }
    return qu;

}

Expression* createExpression(queue<string> qu) {
    stack<Expression*> st;
    string curr;

    while(!qu.empty()) {
        curr = qu.front();
        qu.pop();
        if(curr == "/") {
            Expression* right = st.top();
            st.pop();
            Expression* left = st.top();
            st.pop();
            st.push(new Div(left,right));
        }
        else if(curr == "*") {
            Expression* right = st.top();
            st.pop();
            Expression* left = st.top();
            st.pop();
            st.push(new Mul(left,right));
        }
        else if(curr == "-") {
            Expression* right = st.top();
            st.pop();
            Expression* left = st.top();
            st.pop();
            st.push(new Minus(left,right));
        }
        else if(curr == "+") {
            Expression* right = st.top();
            st.pop();
            Expression* left = st.top();
            st.pop();
            st.push(new Plus(left,right));
        }
        else {
            //its number or var
            try {
                double val = std::stod(curr);
                st.push(new Val(val));
            }
            catch(const std::exception& e) {
                //It not a number its a var
                st.push(new Var(curr));
            }
        }
    }
    Expression* result = st.top();
    st.pop();
    /*
    if (!st.empty()) {
        //Speical case - we had minus at the end - just sum the expressions
        Expression* left = st.top();
        st.pop();

        return new Plus(left, result);
    }*/
    return result;
}
bool isNumber(string check) {
    if (MapsHandler::isVarExsist(check)) {
        return true;
    }
    try {
        std::stod(check);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

Expression* ExpressionBuilder::getExpression (vector<string>::iterator &it, vector<string>::iterator end) {
    vector<string>::iterator begin = it;

    vector<string>::iterator pos = it;
    pos++;
    while (pos != end && ((*pos).at(0)!='<' && (*pos).at(0)!='>' && (*pos).at(0)!='=') && !((isNumber(*it) && ((*pos) == "(" || isNumber(*pos))))) {
        it++;
        pos++;
    }
    it++;





    /**
    if (*it == "-") {
        it = it + 2;
    } else {
        it++;
    }
    while(it != end && (*it == "+" || *it == "-" || *it == "/" || *it == "*")) {
        //add the number after the symbol and check the next string
        it = it+2;
    }
     */
    vector<string> expressions = vector<string>(begin,it);
    checkNegative(expressions);
    //Now I have begin for the beginning of the expression and it point to the end of it
    queue<string> express = shuntingYard(expressions);
    return createExpression(express);

}

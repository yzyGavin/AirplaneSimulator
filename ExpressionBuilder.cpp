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
/**
 * the method adds brackets to expressions with '/' operator
 */
void addBrackets(vector<string> &expressions) {
    vector<string>::iterator temp;
    for (vector<string>::iterator it = expressions.begin(); it != expressions.end(); it++) {
        // if we found a '/'
        if (*it == "/") {
            //if there isnt ')' after the '/'
            if (*(it+1) != ")") {
                it = expressions.insert(it + 2, ")");
                temp = it - 3;
                // find the position for the '('
                if (temp != expressions.begin() && (temp - 1) != expressions.begin()) {
                    temp = temp - 2;
                    if (*(temp) == "/") {
                        //bool first = true;
                        int count = 1;
                        while (*temp != ")" && !(count == 0)) {
                            if (*temp == "(") {
                                count--;
                            } else if (*temp == ")") {
                                count++;
                            }
                            if (temp != expressions.begin()) {
                                temp--;
                            }
                        }
                        temp = expressions.insert(temp, "(");
                    } else {
                        temp = expressions.insert(temp, "(");
                    }
                } else {
                    expressions.insert(it - 3, "(");
                }
            }
        }
    }
}


/**
 * the method check if there are '-' in the expression and adds brackets accordingly
 */
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
            next = expressions.insert(it, "(");
            //next is on the ( : next+1 is after the (
            next = expressions.insert(next+1, "0");
            //next is on the ( : next+ is after the - and the number
            next = expressions.insert(next+3, ")");
            it = next;
        }
        lastBracket = false;
        lastOperator = false;
    }
}
/**
 * the method inserts the strings into the queue according to shunting yard algotirthm
 */
queue<string> shuntingYard(vector<string> objects) {
    stack <string> st;
    queue <string> qu;
    for(vector<string>::iterator it = objects.begin(); it != objects.end(); it++) {
        if (*it == "+" || *it == "-" ) {
            //They have a greater precendence
            while(!st.empty() && (st.top() == "/" || st.top() == "*" || st.top() == "-" || st.top() == "+")) {
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
/**
 * the method builds the expression object from the srtings in the queue
 */
Expression* createExpression(queue<string> qu) {
    stack<Expression*> st;
    string curr;
    // just the way to move from infix to postfix
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
    return result;
}
/**
 * the method checks if a string represents a double
 */
bool isNumber(string check) {
    if (MapsHandler::isVarExist(check)) {
        return true;
    }
    try {
        std::stod(check);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}
/**
 * the metho builds an expression from vector of strings
 */
Expression* ExpressionBuilder::getExpression (vector<string>::iterator &it, vector<string>::iterator end) {
    vector<string>::iterator begin = it;

    vector<string>::iterator pos = it;
    pos++;
    //take the string for thewxpression- now more and not less
    while (pos != end && ((*pos).at(0)!='<' && (*pos).at(0)!='>' && (*pos).at(0)!='=') && !((isNumber(*it) && ((*pos) == "(" || isNumber(*pos))))) {
        it++;
        pos++;
    }
    it++;
    vector<string> expressions = vector<string>(begin,it);
    checkNegative(expressions);
    addBrackets(expressions);
    //Now I have begin for the beginning of the expression and it point to the end of it
    queue<string> express = shuntingYard(expressions);
    return createExpression(express);

}

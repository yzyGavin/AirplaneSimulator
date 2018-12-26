//
// Created by ofir8 on 12/20/18.
//

#include "PrintCommand.h"

void PrintCommand::doCommand() {
    // if its just a string
    if (params.at(0).at(0) == '"' && (params.end() - 1)->back() == '"') {
        params.at(0) = params.at(0).substr(1, std::string::npos);
        (params.end() - 1)->pop_back();
        cout << params.at(0) << endl;
    } else { // if we need to calculate it
        vector<string>::iterator it = params.begin();
        Expression* ex = ExpressionBuilder::getExpression(it, params.end());
        if (it != params.end()) {
            cout << "wrong input" << endl;
            delete(ex);
            return;
        }
        cout << ex->calculate() << endl;
        delete(ex);
    }
}
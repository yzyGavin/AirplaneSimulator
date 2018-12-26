//
// Created by ofir8 on 12/20/18.
//

#include "SetCommand.h"
#include "MapsHandler.h"
#include "ComunicateWithSimulator.h"
/**
 * constructor
 */
SetCommand::SetCommand(vector<string> vec) {
    var = *vec.begin();
    sign = vec.at(1);
    params = vector<string>(vec.begin() + 2, vec.end());
}
/**
 * the method sets the value to the var
 */
void SetCommand::doCommand() {
    if (sign != "=" || !MapsHandler::isVarExist(var)) {
        cout << "wrong input" << endl;
        return;
    }
    Expression* ex;
    vector<string>::iterator it = params.begin();
    //It's a set
    ex = ExpressionBuilder::getExpression(it, params.end());
    //make sure it finished all the strings
    if (it != params.end()) {
        cout << "wrong input" << endl;
        delete(ex);
        return;
    }
    double value = ex->calculate();
    delete(ex);
    MapsHandler::addVar(var, value);
    //if there is a bind - we need to inform all the vars in the bind
    while (MapsHandler::isBindExist(var)) {
        if(MapsHandler::isAddressExist(MapsHandler::getVarAddress(var))) {
            MapsHandler::addToAddresses(MapsHandler::getVarAddress(var), value);
            ComunicateWithSimulator::sendToServer(var, value);
            break;
        }
        else {
            var = MapsHandler::getVarAddress(var);
            MapsHandler::addVar(var, value);
        }
    }
}
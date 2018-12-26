//
// Created by ofir8 on 12/20/18.
//

#include "SetCommand.h"
#include "MapsHandler.h"
#include "ComunicateWithSimulator.h"

SetCommand::SetCommand(vector<string> vec) {
    var = *vec.begin();
    sign = vec.at(1);
    params = vector<string>(vec.begin() + 2, vec.end());
}

void SetCommand::doCommand() {
    if (sign != "=" || !MapsHandler::isVarExsist(var)) {
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
    /*if (MapsHandler::isBindExsist(var)) {
        //MapsHandler::addToAddresses(MapsHandler::getVarAddress(var), value);
        ComunicateWithSimulator::sendToServer(var, value);
    }
    while (MapsHandler::isBindExsist(var)) {
        if(MapsHandler::isBindExsist(MapsHandler::getVarAddress(var))) {
            var = MapsHandler::getVarAddress(var);
            MapsHandler::addVar(var, value);
        }
        else {
            MapsHandler::addToAddresses(MapsHandler::getVarAddress(var), value);
            ComunicateWithSimulator::sendToServer(var, value);
        }
    }*//*
    while (MapsHandler::isBindExsist(var)) {
        if (MapsHandler::isBindExsist(MapsHandler::getVarAddress(var))) {
            var = MapsHandler::getVarAddress(var);
            MapsHandler::addVar(var, value);
        }
        else if ()
        else {
            MapsHandler::addToAddresses(MapsHandler::getVarAddress(var), value);
            ComunicateWithSimulator::sendToServer(var, value);
        }
    }*/
    while (MapsHandler::isBindExsist(var)) {
        if(MapsHandler::isAddressExsist(var)) {
            /*var = MapsHandler::getVarAddress(var);
            MapsHandler::addVar(var, value);*/
            MapsHandler::addToAddresses(MapsHandler::getVarAddress(var), value);
            cout << MapsHandler::getVarAddress(var) << " val is:" << MapsHandler::getVarValue(var);
            ComunicateWithSimulator::sendToServer(var, value);
        }
        /*else if (MapsHandler::isBindExsist(MapsHandler::getVarAddress(var))) {

        }*/
        else {
            /*MapsHandler::addToAddresses(MapsHandler::getVarAddress(var), value);
            ComunicateWithSimulator::sendToServer(var, value);*/
            var = MapsHandler::getVarAddress(var);
            MapsHandler::addVar(var, value);
        }
    }
}
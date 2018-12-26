//
// Created by ofir8 on 12/20/18.
//

#include "VarCommand.h"

void VarCommand::doCommand() {
    if (params.at(1) != "=") {
        cout << "wrong input" << endl;
        return;
    }
    string varName = params.at(0);
    if (params.at(2) == "bind") {
        //FOR TESTING - REMOVE
        MapsHandler::createAddressTable();
        //
        string address = "";
        for(vector<string>::iterator it = params.begin() + 3; it != params.end(); it++) {
            address += *it;
        }
        if(address.find("\"") != std::string::npos) {
            address.erase(address.find("\""),1);
            address.erase(address.find("\""),1);
        }
        if (!MapsHandler::isAddressExsist(address) && !MapsHandler::isVarExsist(address)) {
            cout << "wrong input" << endl;
            return;
        }
        if (!MapsHandler::isAddressExsist(address)) {
            MapsHandler::addBind(varName, address);
            MapsHandler::addVar(varName, MapsHandler::getVarValue(address));
        }
        else {
            cout << "is a address bind varName: " << varName << " address: "  << address << endl;
            MapsHandler::addBind(varName, address);
            MapsHandler::addVar(varName, MapsHandler::getValOfAddress(address));
        }
    } else {
        vector<string>::iterator it = params.begin() + 2;
        Expression* ex = ExpressionBuilder::getExpression(it, params.end());
        if (it != params.end()) {
            cout << "wrong input" << endl;
            delete(ex);
            return;
        }
        MapsHandler::addVar(varName, ex->calculate());
        delete(ex);
    }
}
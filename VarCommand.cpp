//
// Created by ofir8 on 12/20/18.
//

#include "VarCommand.h"
/**
 * add the var to the maps
 */
void VarCommand::doCommand() {
    if (params.at(1) != "=") {
        cout << "wrong input" << endl;
        return;
    }
    string varName = params.at(0);
    if (params.at(2) == "bind") {
        // if its a bind,
        string address = "";
        for(vector<string>::iterator it = params.begin() + 3; it != params.end(); it++) {
            address += *it;
        }
        // if it starts and and with "
        if(address.find("\"") != std::string::npos) {
            address.erase(address.find("\""),1);
            address.erase(address.find("\""),1);
        }
        // add to the maps
        if (!MapsHandler::isAddressExist(address) && !MapsHandler::isVarExist(address)) {
            MapsHandler::addToAddresses(address,0);
            MapsHandler::addVar(varName,MapsHandler::getValOfAddress(address));
            MapsHandler::addBind(varName,address);
        }
        if (!MapsHandler::isAddressExist(address)) {
            MapsHandler::addBind(varName, address);
            MapsHandler::addVar(varName, MapsHandler::getVarValue(address));
        }
        else {
            MapsHandler::addBind(varName, address);
            MapsHandler::addVar(varName, MapsHandler::getValOfAddress(address));
        }
    } else {
        // if its not a bind- just add it to the symbol table
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
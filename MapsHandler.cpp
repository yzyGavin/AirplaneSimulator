//
// Created by ofir8 on 12/19/18.
//

#include "MapsHandler.h"

void MapsHandler::createAddressTable() {
    addresses.insert(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    addresses.insert(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/encoder/indicated-altitude-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/encoder/pressure-alt-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/gps/indicated-altitude-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/gps/indicated-ground-speed-kt", 0));
    addresses.insert(pair<string, double>("/instrumentation/gps/indicated-vertical-speed", 0));
    addresses.insert(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    addresses.insert(pair<string, double>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
    addresses.insert(pair<string, double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    addresses.insert(pair<string, double>("/controls/flight/aileron", 0));
    addresses.insert(pair<string, double>("/controls/flight/elevator", 0));
    addresses.insert(pair<string, double>("/controls/flight/rudder", 0));
    addresses.insert(pair<string, double>("/controls/flight/flaps", 0));
    addresses.insert(pair<string, double>("/controls/engines/engine/throttle", 0));
    addresses.insert(pair<string, double>("/engines/engine/rpm", 0));
}
void MapsHandler::updateFromSimulater(vector<double> params) {
    addresses.begin()->second = params.at(21);
    addresses.find("/engines/engine/rpm")->second = params.at(22);
    map<string, double>::iterator it = addresses.find("/instrumentation/airspeed-indicator/indicated-speed-kt");
    int i = 0;
    for (; it != addresses.end(); it++, i++) {
        it->second = params.at(i);
    }
    it = addresses.find("/engines/engine/rpm");
    map<string ,double>::iterator start = addresses.begin();
    start++;
    for (; start != it; start++, i++) {
        start->second = params.at(i);
    }
}
void MapsHandler::addToAddresses(string address,double val) {
    if (addresses.find(address) == addresses.end()) {
        addresses.insert(pair<string, double>(address, val));
    } else {
        addresses.find(address)->second = val;
    }
}
bool MapsHandler::isAddressExsist(string address) {
    return (addresses.find(address) != addresses.end());
}
double MapsHandler::getValOfAddress (string address) {
    if (addresses.find(address) == addresses.end()) {
        cout << "wrong input" << endl;
        return NULL;
    } else {
        return addresses.find(address)->second;
    }
}
void MapsHandler::addVar(string varName,double val) {
    if (symbolTable.find(varName) == symbolTable.end()) {
        symbolTable.insert(pair<string, double> (varName, val));
    } else {
        symbolTable.find(varName)->second = val;
    }
}
bool MapsHandler::isVarExsist(string varName) {
    return (symbolTable.find(varName) != symbolTable.end());
}
double MapsHandler::getVarValue (string varName) {
    if (symbolTable.find(varName) == symbolTable.end()) {
        cout << "wrong input" << endl;
        return NULL;
    }
    if (binds.find(varName) != binds.end()) {
        cout << "bind founded" << endl;
        if(MapsHandler::isAddressExsist(binds.find(varName)->second)) {
            cout << "DIrect" << endl;
            return addresses.find(binds.find(varName)->second)->second;
        }
        else {
            cout << "inDirect " << binds.find(varName)->second << endl;
            return MapsHandler::getVarValue(binds.find(varName)->second);
        }
    }
    cout << "not bind" << endl;
    return symbolTable.find(varName)->second;
}

void MapsHandler::addBind(string varName,string address) {
    binds.insert(pair<string, string> (varName, address));
}
bool MapsHandler::isBindExsist(string varName) {
    return (binds.find(varName) != binds.end());
}
string MapsHandler::getVarAddress (string varName) {
    if (binds.find(varName) == binds.end()) {
        cout << "wrong input" << endl;
        return NULL;
    }
    return binds.find(varName)->second;
}


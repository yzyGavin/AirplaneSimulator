//
// Created by ofir8 on 12/19/18.
//

#ifndef PROJECTDEMO_MAPSHANDLER_H
#define PROJECTDEMO_MAPSHANDLER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

static map<string, double> addresses;
static map<string, double> symbolTable;
static map<string, string> binds;
static map<string, double> notXML;

class MapsHandler {
public:
    static void createAddressTable();
    static void updateFromSimulater(vector<double> params);
    static void addToAddresses(string address,double val);//
    static bool isAddressExsist(string address);//
    static double getValOfAddress (string address);//
    static void addVar(string varName,double val);//
    static bool isVarExsist(string varName);
    static double getVarValue (string varName);
    static void addBind(string varName,string address);
    static bool isBindExsist(string varName);
    static string getVarAddress (string varName);
};



#endif //PROJECTDEMO_MAPSHANDLER_H

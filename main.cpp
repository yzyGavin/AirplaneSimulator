#include <iostream>
#include <vector>
#include <map>

#include "MapsHandler.h"
#include "Command.h"
#include "OpenDataServerFactory.h"
#include "ConnectFactory.h"
#include "IfFactory.h"
#include "WhileFactory.h"
#include "CommandFactory.h"
#include "PrintFactory.h"
#include "SetFactory.h"
#include "VarFactory.h"
#include "SleepFactory.h"


#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <fstream>

using namespace std;


/**
 * the method splits the line to vector of strings
*/
vector<string> lexer(const string &line) {
    vector<string> vec;
    std::size_t prev = 0, pos;
    if (line.find("print") == 0) {
        //It a print
        if (line.find('"') != std::string::npos) {
            vec.push_back("print");
            vec.push_back(line.substr(line.find('"'), line.length() - line.find('"')));
            return vec;
        }
    }
    // we want to split by one of: " +-*/()<>=!{"
    while ((pos = line.find_first_of(" +-*/()<>=!{", prev)) != std::string::npos)
    {
        if (pos > prev) {
            vec.push_back(line.substr(prev, pos - prev));
            if (line.at(pos) != ' ') {
                if (pos + 1 < line.length() && line.at(pos+1) == '=') {
                    vec.push_back(line.substr(pos, 2));
                    prev = pos + 2;
                } else {
                    vec.push_back(line.substr(pos, 1));
                    prev = pos + 1;
                }
            } else {
                prev = pos+1;
            }
        } else if (pos == prev) {
            if (line.at(pos) != ' ') {
                if (pos + 1 < line.length() && line.at(pos+1) == '=') {
                    vec.push_back(line.substr(pos, 2));
                    prev = pos + 2;
                } else {
                    vec.push_back(line.substr(pos, 1));
                    prev = pos + 1;
                }
            } else {
                prev = pos+1;
            }
        }
    }
    if (prev < line.length()) {
        vec.push_back(line.substr(prev, std::string::npos));
    }
    return vec;
}
/**
 * creates the commands from the strings
 */
Expression* parser(vector<string> &vec, const map<string, CommandFactory*> *commandMap) {
    if (commandMap->find(vec.at(0)) == commandMap->end()) {
        if (vec.at(1) == "=") {
            return commandMap->at("=")->getCommand(vec, vector<Expression*>());
        } else {
            cout << "wrong input" << endl;
            return nullptr;
        }
    } else {
        vector<string> params(vec.begin() + 1, vec.end());
        return commandMap->at(vec.at(0))->getCommand(params, vector<Expression*>());
    }
}
/**
 * in case we have if/while- create a condition command - with condition and list of commands it should execute
 */
Expression* loopParser(vector<string> &vec, const map<string, CommandFactory*> *commandMap, std::istream &in) {
    if (vec.at(1) == "(") {
        if (*(vec.end() - 1) != ")") {
            cout << "wrong input" << endl;
            return nullptr;
        }
        vec.erase(vec.begin() + 1);
        vec.erase(vec.end() - 1);
    }
    string line;
    vector<Expression*> commands;
    Expression* command;
    vector<string> currLine;

    getline (in, line);
    currLine = lexer(line);
    do {
        // if we have another if/while inside
        if (currLine.back() == "{") {
            currLine.pop_back();
            command = loopParser(currLine, commandMap, in);
        } else {
            command = parser(currLine, commandMap);
        }
        commands.push_back(command);
        getline (in, line);
        currLine = lexer(line);
    } while (currLine.back() != "}");
    currLine.pop_back();
    if (currLine.begin() != currLine.end()) {
        command = parser(currLine, commandMap);
        commands.push_back(command);
    }
    vector<string> params(vec.begin() + 1, vec.end());
    return commandMap->at(vec.at(0))->getCommand(params, commands);
}
/**
 * create the commandFactory- map
 */
void createCommandMap(map<string, CommandFactory*>* commandMap) {
    commandMap->insert(pair<string, CommandFactory*>("openDataServer", new OpenDataServerFactory()));
    commandMap->insert(pair<string, CommandFactory*>("connect", new ConnectFactory()));
    commandMap->insert(pair<string, CommandFactory*>("var", new VarFactory()));
    commandMap->insert(pair<string, CommandFactory*>("if", new IfFactory()));
    commandMap->insert(pair<string, CommandFactory*>("while", new WhileFactory()));
    commandMap->insert(pair<string, CommandFactory*>("print", new PrintFactory()));
    commandMap->insert(pair<string, CommandFactory*>("=", new SetFactory()));
    commandMap->insert(pair<string, CommandFactory*>("sleep", new SleepFactory()));
}
/**
 * the main func
 */
int main(int argc, char *argv[]) {
    //build the commandFactory map
    map<string, CommandFactory*>* commandMap = new map<string, CommandFactory*>();
    createCommandMap(commandMap);
    string line;

    bool fromFile = false;
    std::ifstream f;
    // if we should read the script from the file
    if (argc == 2) {
        f.open(argv[1]);
        fromFile = true;
    }
    std::istream &in = (argc == 2) ? f : std::cin;


    bool lastline = false;
    while (true) {
        getline (in, line);
        if (!fromFile &&line == "exit"  || lastline) {
            break;
        }
        if(fromFile && in.eof()) {
            lastline = true;
        }
        vector<string> vec = lexer(line);
        Expression* command;
        // if its a if/while command
        if (vec.back() == "{") {
            vec.pop_back();
            command = loopParser(vec, commandMap, in);
        }
        else {
            command = parser(vec, commandMap);
        }
        command->calculate();
        delete(command);
    }

    //Delete the factory
    map<string, CommandFactory*>::iterator it = commandMap->begin();
    for (; it != commandMap->end(); it++) {
        delete (it->second);
    }
    delete (commandMap);


    //closeTwoSockets and the thread
    ComunicateWithSimulator::closeAll();
    //Close the file if open
    if (fromFile) {
        f.close();
    }

    return 0;
}
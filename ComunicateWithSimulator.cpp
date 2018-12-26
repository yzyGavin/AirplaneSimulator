//
// Created by ofir8 on 12/19/18.
//

#include <unistd.h>
#include "ComunicateWithSimulator.h"
#include "MapsHandler.h"
int ComunicateWithSimulator::sockfd = 0;
bool ComunicateWithSimulator::sendToServer(string st, double val) {
    string command = "set " + MapsHandler::getVarAddress(st) + " " + std::to_string(val) + " \r\n";
    const char* tosend = command.c_str();
    size_t le = command.length();
    int n = write(sockfd, command.c_str(), command.length());

    if (n < 0) {
        return false;
    }
    return true;
}
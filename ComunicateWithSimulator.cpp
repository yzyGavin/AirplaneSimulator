//
// Created by ofir8 on 12/19/18.
//

#include <unistd.h>
#include "ComunicateWithSimulator.h"
#include "MapsHandler.h"
int ComunicateWithSimulator::sockfd = -1;
int ComunicateWithSimulator::DataServerSocket = -1;
pthread_t* ComunicateWithSimulator::th = 0;
bool ComunicateWithSimulator::isServerOpen = false;
bool ComunicateWithSimulator::sendToServer(string st, double val) {
    string command = "set " + MapsHandler::getVarAddress(st)
                        + " " + std::to_string(val) + " \r\n";
    //flush(sockfd);
    int n = write(sockfd, command.c_str(), command.length());
    if (n < 0) {
        return false;
    }
    return true;
}

double ComunicateWithSimulator::getFromServer(string address) {
    string query = "get " + address  + " \r\n";
    int n = write(sockfd, query.c_str(), query.length());

    //Get Result
    char buffer[200];
    n = read(sockfd,buffer,200);
    if (n < 0) {
        return 0;
    }
    string result = std::string(buffer);
    int start = result.find("'");
    result = result.substr(start + 1);
    int end = result.find("'");
    result = result.substr(0, end);
    return stod(result);
}

void ComunicateWithSimulator::closeAll() {
    //Close the client socket to the simulator
    if (sockfd > 0) {
        close(sockfd);
    }

    //Close Data Server Socket
    if (DataServerSocket > 0) {
        isServerOpen = false;
        close(DataServerSocket);
    }

    //Wait for the thread to close
    sleep(1);
}
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

/**
 * the method sends to the simulator the address st with the value val
 */
bool ComunicateWithSimulator::sendToServer(string st, double val) {
    //Create string of the commnad
    string command = "set " + MapsHandler::getVarAddress(st)
                        + " " + std::to_string(val) + " \r\n";

    //Send to server
    int n = write(sockfd, command.c_str(), command.length());
    //make sure the massage sent successfully
    if (n < 0) {
        return false;
    }
    return true;
}
/**
 * the method asks from the simulator for value of some address and save the result
 */
double ComunicateWithSimulator::getFromServer(string address) {
    //Get command
    string query = "get " + address  + " \r\n";
    //Send to the server the command
    int n = write(sockfd, query.c_str(), query.length());

    //Get Result
    char buffer[200];
    n = read(sockfd,buffer,200);
    if (n < 0) {
        return 0;
    }
    //Substring only the double
    string result = std::string(buffer);
    int start = result.find("'");
    result = result.substr(start + 1);
    int end = result.find("'");
    result = result.substr(0, end);
    return stod(result);
}
/**
 * the method closes the client and server sockets and the thread we created
 */
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
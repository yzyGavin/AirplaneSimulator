//
// Created by ofir8 on 12/20/18.
//

#include "ConnectToServerCommand.h"
void ConnectToServerCommand::doCommand () {
    string ip = params.at(0);
    // build the port
    vector<string>::iterator it = params.begin() + 1;
    Expression* portno = ExpressionBuilder::getExpression(it, params.end());
    if (it != params.end() || portno == nullptr) {
        //we have unused word
        cout << "wrong input" << endl;
        return;
    }
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    // Create a socket point
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    server = gethostbyname(ip.c_str());
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno->calculate());
    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    //Send to the server handler the socket
    ComunicateWithSimulator::setSocketNumber(sockfd);
    delete (portno);
}
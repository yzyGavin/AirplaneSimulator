//
// Created by ofir8 on 12/20/18.
//

#include "OpenDataServerCommand.h"



void handle_input_params(string line) {
    int place = line.find(" ");
    string address = line.substr(0, place);
    double value = stod(line.substr(place + 1, line.length() - place - 2));
    MapsHandler::addToAddresses(address, value);
}

void *openServer(void* params) {
    int sockfd, newsockfd, clilen;
    char buffer[400];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;
    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    int* arr = (int*)params;
    int p = *arr;
    int h = *(arr + 1);
    serv_addr.sin_port = htons(p);
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */
    listen(sockfd,1);
    clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    newsockfd = ::accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    cout << "connected" << endl;
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    bzero(buffer,400);
    string line = "";
    string prevline = "";
    vector<double> vec;
    MapsHandler::createAddressTable();
    while (true) {
        int pos,prev = 0;
        /* If connection is established then start communicating */
        n = read(newsockfd,buffer,400);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        /*line.clear();
        line += prevline;
        line += std::string(buffer);
        prevline = line.substr(line.find('\n') + 1);
        line = line.substr(0, line.find('\n'));
        cout << line << endl;*/
        line += std::string(buffer);
        if ("exit" == std::string(buffer)) {
            cout << "simulator disconncted" << endl;
            break;
        }
        line = line.erase(line.find_first_of("\n"),1);
        for (int i = 0; i < 22; i++) {
            pos = line.find_first_of(",");
            vec.push_back(stod(line.substr(0,pos)));
            line.erase(0, pos + 1);
        }
        vec.push_back(stod(line.substr(0)));
        line.erase(0, line.length() - 1);
        /*if(line == "exit") {
            cout << "simulator disconncted" << endl;
            break;
        }
        vec.clear();
        while ((pos = line.find_first_of(",", prev)) != std::string::npos)
        {
            if (pos > prev) {
                vec.push_back(stod(line.substr(prev, pos - prev)));
            }
            prev = pos+1;
        }
        if (prev < line.length()) {
            vec.push_back(stod(line.substr(prev, std::string::npos)));
        }*/
        MapsHandler::updateFromSimulater(vec);
        // when the
        //sleep(1.0/h);
    }
    delete(arr);
}
void OpenDataServerCommand::doCommand() {
    vector<string>::iterator it = params.begin();
    // build the first expression - port
    Expression* port = ExpressionBuilder::getExpression(it, params.end());
    // build the second expression - hz
    Expression* hz = ExpressionBuilder::getExpression(it, params.end());
    if (it != params.end()) {
        //we have unused word
        cout << "wrong input" << endl;
        return;
    }
    pthread_t server;
    int p = (int)port->calculate();
    int h = (int)hz->calculate();
    int* arr = new int(2);
    arr[0] = p;
    arr[1] = h;
    delete (port);
    delete (hz);
    pthread_create(&server, nullptr, &openServer, (void*)arr);
}
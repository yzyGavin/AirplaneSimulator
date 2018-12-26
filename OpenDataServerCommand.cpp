//
// Created by ofir8 on 12/20/18.
//

#include "OpenDataServerCommand.h"
#include "ComunicateWithSimulator.h"

/**
 * the thread.
 * @param params - the port and hz
 */
void *openServer(void* params) {
    int* arr = (int*)params;
    int newsockfd = *arr;
    int h = *(arr + 1);

    char buffer[400];
    int n = 0;

    bzero(buffer,400);
    string line = "";
    string prevline = "";
    vector<double> vec;
    while (ComunicateWithSimulator::isOpen()) {
        int pos,prev = 0;
        /* If connection is established then start communicating */
        n = read(newsockfd,buffer,400);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        line += std::string(buffer);
        if ("exit" == std::string(buffer)) {
            break;
        }
        //line = line.erase(line.find_first_of("\n"),1);
        for (int i = 0; i < 22; i++) {
            pos = line.find_first_of(",");
            vec.push_back(stod(line.substr(0,pos)));
            line.erase(0, pos + 1);
        }
        vec.push_back(stod(line.substr(0, line.find_first_of("\n"))));
        line.erase(0, line.find_first_of("\n") + 1);

        MapsHandler::updateFromSimulator(vec);
        vec.clear();
        sleep(1.0/h);
    }
    delete(arr);
}
/**
 * the method creates the server and a new thread for it
 */
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

    //Create the server
    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int  n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    serv_addr.sin_port = htons(port->calculate());
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
    //Close the welcome server (tcp)
    close(sockfd);

    pthread_t server;
    int h = (int)hz->calculate();
    int* arr = new int(2);
    arr[0] = newsockfd;
    arr[1] = h;


    delete (port);
    delete (hz);

    MapsHandler::createAddressTable();

    char buf;
    //Wait for first input from the client
    int none = recv(newsockfd,&buf,1,MSG_PEEK);
    //Run the thread for the updating
    pthread_create(&server, nullptr, &openServer, (void*)arr);

    //Move the thread and the socket to the Comunicate Calls for close it later
    ComunicateWithSimulator::setOpenDataServer(&newsockfd, &server);


}
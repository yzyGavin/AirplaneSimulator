//
// Created by ofir8 on 12/19/18.
//

#ifndef PROJECTDEMO_COMUNICATEWITHSIMULATOR_H
#define PROJECTDEMO_COMUNICATEWITHSIMULATOR_H

#include <string>
using namespace std;


class ComunicateWithSimulator {
public:
    static int sockfd;
    static void setSocketNumber(int num) {
        sockfd = num;
    }
    static bool sendToServer(string st, double val);
};

#endif //PROJECTDEMO_COMUNICATEWITHSIMULATOR_H

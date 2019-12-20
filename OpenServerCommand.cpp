//
// Created by boris on 20/12/2019.
//

#include <sys/socket.h>
//#include <bits/socket_type.h>
#include <iostream>
#include "ex1.h"
#include "CommandTypes.h"
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

OpenServerCommand::OpenServerCommand(string portStr) {
    Expression *e;
    Interpreter *i1 = new Interpreter();
    e = i1->interpret(portStr);
    this->port = (int) e->calculate();
    this->numberOfArgs = 1;
}

double OpenServerCommand::execute() {
    thread t1(startSocket());
    t1.join();
    return 1 + numberOfArgs;
}

int OpenServerCommand::startSocket() {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        cerr << "could not create a socket" << endl;
        //return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not bind the socket to an IP" << endl;
        //return -2;
    }
    if (listen(socketfd, 5) == -1) {
        cerr << "Error during listening command" << endl;
        // return -3;
    }

    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
    if (client_socket == -1) {
        cerr << "Error accepting client" << endl;
        //return -4;
    }



    //close(socketfd);

}



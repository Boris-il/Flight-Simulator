//
// Created by boris on 20/12/2019.
//

#include "CommandTypes.h"
#include "ex1.h"
#include <sys/socket.h>
//#include <bits/socket_type.h>
#include <iostream>
#include "CommandTypes.h"
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

ConnectCommand::ConnectCommand(const char *ipStr, string portStr) {
    this->numberOfArgs = 2;
    this->ip = ipStr;
    Expression *e;
    Interpreter *i1 = new Interpreter();
    e = i1->interpret(portStr);
    this->port = (int) e->calculate();
}

double ConnectCommand::execute() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        cerr << "could not create a socket" << endl;
        return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(this->ip);
    address.sin_port = htons(this->port);

    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Could not connect to host server" << endl;
        return -2;
    } else {
        cout << "Client is now connected to server" << endl;
    }

    //close(socketfd);

}



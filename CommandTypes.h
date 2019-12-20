//
// Created by boris on 20/12/2019.
//

#ifndef FLIGHT_SIMULATOR_COMMANDTYPES_H
#define FLIGHT_SIMULATOR_COMMANDTYPES_H

#include <string>
#include "Command.h"

class OpenServerCommand : public Command {
    int port;
public:
    OpenServerCommand(string portAsString);

    double execute();

    int startSocket();
};

class ConnectCommand : public Command {
    const char *ip;
    int port;
public:
    ConnectCommand(const char *ipAsString, string portAsString);

    double execute();
};


#endif //FLIGHT_SIMULATOR_COMMANDTYPES_H

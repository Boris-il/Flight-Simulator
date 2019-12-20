//
// Created by boris on 20/12/2019.
//

#ifndef FLIGHT_SIMULATOR_COMMAND_H
#define FLIGHT_SIMULATOR_COMMAND_H


using namespace std;

class Command {

protected:
    int numberOfArgs;
public:
    virtual double execute() = 0;

    virtual ~Command() {};
};


#endif //FLIGHT_SIMULATOR_COMMAND_H

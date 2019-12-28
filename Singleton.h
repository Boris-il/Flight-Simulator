//
// Created by boris on 24/12/2019.
//

#ifndef FLIGHT_SIMULATOR_SINGLETON_H
#define FLIGHT_SIMULATOR_SINGLETON_H

#include "ex3.h"
#include "ex1.h"
#include <map>


class Singleton {
private:
    static Singleton *instance;

    // constructor
    Singleton();

public:
    // interpreter member
    Interpreter *m_inter;
    // commands map
    map<string, Command *> m_commands_map;

    static Singleton *getInstance();

};


#endif //FLIGHT_SIMULATOR_SINGLETON_H

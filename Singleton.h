//
// Created by boris on 24/12/2019.
//

#ifndef FLIGHT_SIMULATOR_SINGLETON_H
#define FLIGHT_SIMULATOR_SINGLETON_H

#include "ex3.h"
#include "ex1.h"


class Singleton {
private:
    static Singleton *instance;

    // constructor
    Singleton();

public:
    // interpreter member
    Interpreter *m_inter;

    static Singleton *getInstance();

};


#endif //FLIGHT_SIMULATOR_SINGLETON_H

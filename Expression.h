//
// Created by boris on 20/12/2019.
//

#ifndef FLIGHT_SIMULATOR_EXPRESSION_H
#define FLIGHT_SIMULATOR_EXPRESSION_H

using namespace std;

class Expression {

public:
    virtual double calculate() = 0;

    virtual ~Expression() {};
};


#endif //FLIGHT_SIMULATOR_EXPRESSION_H

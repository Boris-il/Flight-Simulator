//
// Created by yuval on 23/12/2019.
//
#include "ex1.h"
#include "CommandTypes.h"
#include "chrono"

unsigned int SleepCommand::execute(vector<string>::iterator iterator) {
    Expression *e;
    Interpreter *i1 = new Interpreter();
    if (*iterator == "@") {
        ++iterator;
    }
    string timeStr = *(iterator + 1);
    try {
        e = i1->interpret(timeStr);
        double timeToSleep = e->calculate();
        int t = timeToSleep;
      std::this_thread::sleep_for(std::chrono::milliseconds(t)); //sleep command.

    } catch (const char *ex) {
        cerr << "could not interpret " << timeStr << " in SleepCommand" << endl;
    }

    return 1;
}
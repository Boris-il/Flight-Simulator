//
// Created by yuval on 23/12/2019.
//
#include "ex1.h"
#include "CommandTypes.h"
#include "chrono"

unsigned int SleepCommand::execute(vector<string>::iterator iterator) {
  unsigned index = 0;
  Expression *e;
  Interpreter *i1 = new Interpreter();
  string timeStr = *(iterator + 1);
  e = i1->interpret(timeStr);
  double timeToSleep = e->calculate();
  index = 1;
  int t = timeToSleep;
  std::this_thread::sleep_for(std::chrono::milliseconds(t));
  return index;
}
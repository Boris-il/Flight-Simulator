//
// Created by yuval on 23/12/2019.
//
#include "ex1.h"
#include "CommandTypes.h"
#include "unistd.h"

unsigned int sleepCommand::execute(vector<string>::iterator iterator, unordered_map<string, Var> &map) {
  unsigned index = 0;
  Expression *e;
  Interpreter *i1 = new Interpreter();
  string timeStr = *(iterator + 2);
  e = i1->interpret(timeStr);
  double timeToSleep = e->calculate();
  index = 2;
  usleep(timeToSleep);
  return index;
}
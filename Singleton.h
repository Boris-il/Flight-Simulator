//
// Created by boris on 24/12/2019.
//

#ifndef FLIGHT_SIMULATOR_SINGLETON_H
#define FLIGHT_SIMULATOR_SINGLETON_H

#include "ex3.h"
#include "ex1.h"
#include <map>
#include <mutex>

class Singleton {
 private:
  static Singleton *instance;

  // constructor
  Singleton();

 public:
  // interpreter member
  Interpreter *m_inter;
  bool shouldStop = false;
  std::mutex mutex_lock;
  // commands map
  map<string, Command *> m_commands_map;
  // vars map
  unordered_map<string, Var *> var_map;
  // queue of set commands to send to the server
  queue<string> q_commands_to_send;
  int socketNumber1;
  int socketNumber2;

  static Singleton *getInstance();

};

#endif //FLIGHT_SIMULATOR_SINGLETON_H

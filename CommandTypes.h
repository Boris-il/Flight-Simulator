//
// Created by boris on 20/12/2019.
//

#ifndef FLIGHT_SIMULATOR_COMMANDTYPES_H
#define FLIGHT_SIMULATOR_COMMANDTYPES_H

#include <string>
#include "Command.h"
#include <thread>
#include "ex3.h"
#include "Singleton.h"
#include <list>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
using namespace std;

class ConditionParser : public Command {
 protected:
  list<Command *> m_commands_list;

  virtual unsigned execute(vector<string>::iterator, unordered_map<string, Var> &var_map) = 0;

  void addChild(Command *);

  static bool parseCondition(const string &);

  void makeCommandsList(vector<string>::iterator);

public:
    ConditionParser() {};

    ~ConditionParser() {};
};

class LoopCommand : public ConditionParser {
  unsigned execute(vector<string>::iterator, unordered_map<string, Var> &var_map);

public:
    LoopCommand() {};

    ~LoopCommand() {};
};

class OpenServerCommand : public Command {
 public:
  unordered_map<string, Var> var_map;
  vector<pair<string, float>> sim_value_vect;
  int client_socket;
  unordered_map<string, string> sim_varName;
  OpenServerCommand() {};

  unsigned execute(vector<string>::iterator, unordered_map<string, Var> &var_map);

  vector<pair<string, float>> initXml();

  void receiveData();

  unordered_map<string, string> buildSimNameMap(unordered_map<string, Var> &map);
};

class ConnectCommand : public Command {
 public:
  unordered_map<string, Var> var_map;
  int client_socket;
  ConnectCommand() {};

  unsigned execute(vector<string>::iterator, unordered_map<string, Var> &var_map);

  void setData();
};

class DefineVarCommand : public Command {
 protected:
  Var *v;
  string m_sim_path, m_var_name;
  // "0" for ->
  // "1" for <-
  unsigned m_bound_type = 0;
  unsigned m_scope = 0;
  // is it bound to simulator variable? (var can be custom made)
  bool m_isBound = false;

 public:
  // define constructor
  //DefineVarCommand(Parser &, const string &, const string &, unsigned, unsigned, bool, Var &);
  //DefineVarCommand(vector<string> *);
  DefineVarCommand();

  // define destructor
  ~DefineVarCommand();

  unsigned execute(vector<string>::iterator, unordered_map<string, Var> &) override;
};

class SleepCommand : public Command {
 public:
  unsigned int execute(vector<string>::iterator, unordered_map<string, Var> &) override;
};

class PrintCommand : public Command {
 public:
  unsigned int execute(vector<string>::iterator, unordered_map<string, Var> &) override;
};

#endif //FLIGHT_SIMULATOR_COMMANDTYPES_H

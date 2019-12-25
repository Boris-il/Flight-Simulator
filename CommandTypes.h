//
// Created by boris on 20/12/2019.
//

#ifndef FLIGHT_SIMULATOR_COMMANDTYPES_H
#define FLIGHT_SIMULATOR_COMMANDTYPES_H

#include <string>
#include "Command.h"
#include <thread>
#include "ex3.h"

class OpenServerCommand : public Command {
 public:
  OpenServerCommand() {};

  unsigned execute(vector<string>::iterator, unordered_map<string, Var> &var_map);

  map<string, double> initXml();

  void receiveData(unordered_map<string, Var> &var_map, map<string, double> sim_Vars, int client_socket);
};

class ConnectCommand : public Command {
 public:
  ConnectCommand() {};

  unsigned execute(vector<string>::iterator, unordered_map<string, Var> &var_map);

  void setData(unordered_map<string, Var> &var_map, int client_socket);
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
  DefineVarCommand() {};

  // define destructor
  ~DefineVarCommand();

  unsigned execute(vector<string>::iterator, unordered_map<string, Var> &);
};

class sleepCommand : public Command {
 public:
  unsigned int execute(vector<string>::iterator iterator, unordered_map<string, Var> &map) override;
};

#endif //FLIGHT_SIMULATOR_COMMANDTYPES_H

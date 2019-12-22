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
    int port;
public:
    OpenServerCommand(string portAsString);

    unsigned execute(vector<string> &cmd_vec, unordered_map<string, Var> &var_map);

    void startSocket();
};

class ConnectCommand : public Command {
    const char *ip;
    int port;
public:
    ConnectCommand(const char *ipAsString, string portAsString);

    unsigned execute(vector<string> &cmd_vec, unordered_map<string, Var> &var_map);
    void ConnectStart();
};

class DefineVarCommand : public Command {
protected:
    Parser *p;
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
    DefineVarCommand();

    // define destructor
    ~DefineVarCommand();

    unsigned execute(vector<string> &, unordered_map<string, Var> &);
};


#endif //FLIGHT_SIMULATOR_COMMANDTYPES_H

//
// Created by boris on 20/12/2019.
//

#ifndef FLIGHT_SIMULATOR_EX3_H
#define FLIGHT_SIMULATOR_EX3_H

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include "ex3.h"
//#include "Command.h"
using namespace std;

//bool shouldStop = false;

class Var {
    string m_var_name, m_simPath;

    // "0" for ->
    // "1" for <-
    // "2" for not bound
    unsigned m_bound_type = 0, m_scope = 0;
  double value;

public:
    bool m_isBound = false;
  bool hasValue = false;
    // constructor
    Var(string var_name, bool isBound, unsigned bound_type, string simPath);

    // constructor
    Var() {};

    Var(string var_name, unsigned scope, Var *v);

    // destructor
    ~Var() {};

    // operator ==
    bool operator==(const Var &v) const;

    void setValue(double num);

    string getSim();

    double getValue();

  string getName();

  unsigned int getBoundType();
};

class Command {

 public:
  virtual unsigned execute(vector<string>::iterator) = 0;

  virtual ~Command() {};
};

class Parser {

public:
    // variables map
  // unordered_map<string, Var *> var_map;

    // constructor
    Parser() {};

    // destructor
    ~Parser() {};

    // lexer func declaration
    static vector<string> lexer(const string &);

    // parse func declaration
    void parse(vector<string> &, map<string, Command *>);
};


//class myHashFunction {
//public:
//    // string name is returned as hash function
//    string operator()(const Var& v) const {
//        return v.m_var_name;
//    }
//};
static void populateCommandsMap(vector<string> *, map<string, Command *>);


#endif //FLIGHT_SIMULATOR_EX3_H

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
#include "Command.h"

using namespace std;

class Var {
    string m_sim_path;
    // "0" for ->
    // "1" for <-
    unsigned m_bound_type = 0;
    unsigned m_scope = 0;

public:
    string m_var_name;

    // constructor
    Var(string var_name, unsigned bound_type, unsigned scope) {
        this->m_var_name = var_name;
        this->m_bound_type = bound_type;
        this->m_scope = scope;
    };

    // constructor
    Var(string var_name, unsigned scope, Var *v) {
        this->m_var_name = var_name;
        this->m_scope = scope;
        this->m_bound_type = v->m_bound_type;
    };

    // destructor
    ~Var() {};

    // operator ==
    bool operator==(const Var &v) const {
        return (this->m_var_name == v.m_var_name);
    }
};


class Parser {

public:
    // commands map
    unordered_map<string, Command*> cmd_map;
    // var_map
    map<string, Var> var_map;

    // constructor
    Parser();

    // destructor
    ~Parser() {};

    // lexer func declaration
    static vector<string> lexer(string);

    // parse func declaration
    void parse(const vector<string> &);
};


//class myHashFunction {
//public:
//    // string name is returned as hash function
//    string operator()(const Var& v) const {
//        return v.m_var_name;
//    }
//};

#endif //FLIGHT_SIMULATOR_EX3_H

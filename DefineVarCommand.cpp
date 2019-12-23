//
// Created by boris on 20/12/2019.
//

#include "CommandTypes.h"
#include "ex3.h"
#include <algorithm>

// implement constructor
DefineVarCommand::DefineVarCommand(vector<string> *commands) {
    this->m_commands = commands;
    this->v = nullptr;
};

// implement command execution
unsigned DefineVarCommand::execute(vector<string>::iterator it, unordered_map<string, Var> &var_map) {
    unsigned index = 0;
    string var_name = *(it + 2);
    //string var_name = (*this->m_commands)[this->m_current_index + 2];
    unsigned bound_type;
    if (*(it + 4) == "<=") {
        bound_type = 1;
    } else {
        bound_type = 0;
    }
    string sim_path = *(it + 8);
    // remove the ""
    string::iterator end_pos = remove(sim_path.begin(), sim_path.end(), '"');
    sim_path.erase(end_pos, sim_path.end());
    // create new Var instance
    Var new_var(var_name, true, bound_type, sim_path);
    // insert to var map
    var_map.emplace(var_name, new_var);
    index = 8;

//    if (this->m_isBound) {
//        // create new var
//        Var v(this->m_var_name, this->m_bound_type, this->m_scope);
//        // insert it to the variables map
//        p->var_map.emplace(this->m_var_name, v);
//    } else {
//        Var v(this->m_var_name, this->m_scope, this->v);
//    }
    // return num of indexes to proceed
    return index;
}

// implement destructor
DefineVarCommand::~DefineVarCommand() {
    if (this->v != nullptr) {
        free(this->v);
    }
}
//
// Created by boris on 20/12/2019.
//

#include "CommandTypes.h"
#include "ex3.h"
#include <algorithm>

// implement constructor
//DefineVarCommand::DefineVarCommand(Parser &p, const string &var_name, const string &sim_path, unsigned bound_type,
//                                   unsigned scope, bool isBound, Var &v) {
//    this->numberOfArgs = 4;
//    this->m_var_name = var_name;
//    this->m_sim_path = sim_path;
//    this->m_bound_type = bound_type;
//    this->m_isBound = isBound;
//    this->m_scope = scope;
//    this->p = &p;
//    this->v = &v;
//}
DefineVarCommand::DefineVarCommand() {

};

// implement command execution
unsigned DefineVarCommand::execute(vector<string> &cmd_vec, unordered_map<string, Var> &var_map) {
    string var_name = cmd_vec[1];
    unsigned bound_type;
    if (cmd_vec[2] == "<=") {
        bound_type = 1;
    } else {
        bound_type = 0;
    }
    string sim_path = cmd_vec[4];
    // remove ""
    string::iterator end_pos = remove(sim_path.begin(), sim_path.end(), '"');
    sim_path.erase(end_pos, sim_path.end());
    // create new Var instance
    Var new_var(var_name, true, bound_type, sim_path);
    // insert to var map
    var_map.emplace(var_name, new_var);

//    if (this->m_isBound) {
//        // create new var
//        Var v(this->m_var_name, this->m_bound_type, this->m_scope);
//        // insert it to the variables map
//        p->var_map.emplace(this->m_var_name, v);
//    } else {
//        Var v(this->m_var_name, this->m_scope, this->v);
//    }
    // return num of indexes to proceed
    return this->numberOfArgs;
}

// implement destructor
DefineVarCommand::~DefineVarCommand() {
    if (this->p != nullptr) {
        free(this->p);
    }
    if (this->v != nullptr) {
        free(this->v);
    }
}
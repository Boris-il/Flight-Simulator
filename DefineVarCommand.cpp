//
// Created by boris on 20/12/2019.
//

#include "CommandTypes.h"
#include "ex3.h"

// implement constructor
DefineVarCommand::DefineVarCommand(Parser &p, const string &var_name, const string &sim_path, unsigned bound_type,
                                   unsigned scope, bool isBound, Var &v) {
    this->numberOfArgs = 4;
    this->m_var_name = var_name;
    this->m_sim_path = sim_path;
    this->m_bound_type = bound_type;
    this->m_isBound = isBound;
    this->m_scope = scope;
    this->p = &p;
    this->v = &v;
}

// implement command execution
double DefineVarCommand::execute() {
    if (this->m_isBound) {
        // create new var
        Var v(this->m_var_name, this->m_bound_type, this->m_scope);
        // insert it to the variables map
        p->var_map.emplace(this->m_var_name, v);
    } else {
        Var v(this->m_var_name, this->m_scope, this->v);
    }
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
//
// Created by boris on 20/12/2019.
//

#include "CommandTypes.h"
#include "ex3.h"
#include "Singleton.h"
#include <algorithm>
#include <sstream>
#include <map>

// implement constructor
DefineVarCommand::DefineVarCommand() {
    this->v = nullptr;
};

// implement destructor
DefineVarCommand::~DefineVarCommand() {
    if (this->v != nullptr) {
        free(this->v);
    }
}

// implement command execution
unsigned DefineVarCommand::execute(vector<string>::iterator it) {
    Singleton *s = Singleton::getInstance();
    Expression *e = nullptr;
    bool varExists = false;
    unsigned bound_type;
    double value = 0;
    string var_name = *(it + 1);

    // check if this Var already exists
    auto var_map_itr = s->var_map.find(var_name);
    if (s->var_map.find(var_name) != s->var_map.end()) {
        varExists = true;
    }

    if (*(it + 2) == "=") {
        // calculate the value of Var
        string val_as_str = *(it + 3);
        try {
            e = s->m_inter->interpret(val_as_str);
            value = e->calculate();
        } catch (const char *e) {
            cerr << "error: could not interpret: " << to_string(value) << endl;
        }
        if (varExists) {
            updateExistingVar(s, var_map_itr, var_name, value);
        } else {
            // create new Var
            Var *new_var = new Var(var_name, false, 2, "");
            new_var->setValue(value);
            // insert to var map
            s->var_map[var_name] = new_var;
            // convert the calculated double var to string
            ostringstream strs;
            strs << value;
            val_as_str = strs.str();
            // insert to var map of the interpreter
            s->m_inter->setVariables(var_name + "=" + val_as_str);
        }

        // return num of indexes to proceed in Parser
        return 3;
    }

    // otherwise, check bound direction
    if (*(it + 2) == "<-") {
        bound_type = 1;
    } else {
        bound_type = 0;
    }
    string sim_path = *(it + 4);
    // remove the ""
    string::iterator end_pos = remove(sim_path.begin(), sim_path.end(), '"');
    sim_path.erase(end_pos, sim_path.end());
    // create new Var instance
    Var *new_var = new Var(var_name, true, bound_type, sim_path);
    // insert to var map
    s->var_map[var_name] = new_var;
    if (bound_type == 1) {
        s->m_inter->setVariables(var_name + "=" + "0");
    }

    // return num of indexes to proceed
    return 4;
}

void DefineVarCommand::updateExistingVar(Singleton *s, unordered_map<string, Var *>::iterator itr, string &name_str,
                                         double value) {
    //todo lock?
  s->mutex_lock.lock();
    //update value of Var in local map
    itr->second->setValue(value);
  s->m_inter->setVariables(name_str + "=" + to_string(value));
    // add update command of this Var to the queue
  string s1 = "set ";
    s1.append(itr->second->getSim() + " ");
    s1.append(to_string(value));
    s1.append("\r\n");
    string msg = s1;
    // add to the queue
    s->q_commands_to_send.push(msg);
    //todo unlock?
  s->mutex_lock.unlock();

}
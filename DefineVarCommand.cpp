//
// Created by boris on 20/12/2019.
//

#include "CommandTypes.h"
#include "ex3.h"
#include "Singleton.h"
#include <algorithm>
#include <sstream>

// implement constructor
DefineVarCommand::DefineVarCommand() {
    this->v = nullptr;
};

// implement command execution
unsigned DefineVarCommand::execute(vector<string>::iterator it, unordered_map<string, Var> &var_map) {
    Singleton *s = Singleton::getInstance();
    Expression *e = nullptr;

    string var_name = *(it + 1);
    if (*(it + 2) == "=") {
        string val_as_str = *(it + 3);
        e = s->m_inter->interpret(val_as_str);
        double value = e->calculate();
        auto pos = var_map.find(var_name);
        if (pos != var_map.end()) {
            //Var var_to_update = pos->second;
            pos->second.setValue(value);
        } else {
            // create new var
            Var new_var(var_name, false, 2, "");
            new_var.setValue(value);
            // insert to var map
            var_map[var_name] = new_var;
        }
        // convert the calculated double var to string
        ostringstream strs;
        strs << value;
        val_as_str = strs.str();
        // insert to var map of the interpreter
        s->m_inter->setVariables(var_name + "=" + val_as_str);
        // return num of indexes to proceed
        return 3;
    }

    unsigned bound_type;
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
    Var new_var(var_name, true, bound_type, sim_path);
    // insert to var map
    var_map.emplace(var_name, new_var);
  if (bound_type == 1) {
    s->m_inter->setVariables(var_name + "=" + "0");
  }

    // return num of indexes to proceed
    return 4;

}

// implement destructor
DefineVarCommand::~DefineVarCommand() {
    if (this->v != nullptr) {
        free(this->v);
    }
}
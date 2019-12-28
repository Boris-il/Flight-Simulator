//
// Created by boris on 27/12/2019.
//

#include "ex3.h"
#include "CommandTypes.h"
#include "Singleton.h"
#include <iostream>


unsigned LoopCommand::execute(vector<string>::iterator it, unordered_map<string, Var> &var_map) {
    this->makeCommandsList(it);
    string condition_str;
    unsigned currentIndex = 0;
    auto temp_it = it;

    while (*(temp_it + 1) != "{") {
        condition_str.append(*(temp_it + 1));
        ++temp_it;
    }
    temp_it += 2;

    while (parseCondition(condition_str)) {
        for (auto list_itr = this->m_commands_list.begin(); list_itr != this->m_commands_list.end(); ++list_itr) {
            Command *c = *(list_itr);
            currentIndex = c->execute(temp_it, var_map);
            temp_it += (currentIndex + 1);
        }
    }
    return temp_it - it;
}




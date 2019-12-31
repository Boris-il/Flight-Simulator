//
// Created by boris on 27/12/2019.
//

#include "ex3.h"
#include "CommandTypes.h"
#include "Singleton.h"
#include <iostream>

unsigned LoopCommand::execute(vector<string>::iterator it) {
    //cout << "in while loop" << endl;
    Singleton *s = Singleton::getInstance();
    // make list of commands to execute in each iteration
    this->makeCommandsList(it);
    string condition_str;
    unsigned currentIndex = 0;
    auto temp_it = it;
    bool wasInLoop = false;

    // get the condition expression as string
    while (*(temp_it + 1) != "{") {
        condition_str.append(*(temp_it + 1));
        ++temp_it;
    }
    temp_it += 2;

    auto after_cond_it = temp_it;

    // execute commands in the list until the conditionParser returns true
    while (parseCondition(condition_str)) {
        wasInLoop = true;
        temp_it = after_cond_it;

        // execute the commands by order
        for (auto list_itr = this->m_commands_list.begin(); list_itr != this->m_commands_list.end(); ++list_itr) {
            Command *c = *list_itr;
            currentIndex = c->execute(temp_it);
            temp_it += (currentIndex + 1);
            if (*temp_it != "@" && *temp_it != "}") {
                ++temp_it;
            }
        }

    }
    if (!wasInLoop) {
        while (*temp_it != "}") {
            ++temp_it;
        }
    }

    // clear the commands list until next condition loop
    this->m_commands_list.clear();
    if (!this->m_commands_list.empty()) {
        cerr << "list not clear" << endl;
    }

    // return index num to proceed to next command in parser
    return temp_it - it;

}




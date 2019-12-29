//
// Created by boris on 27/12/2019.
//

#include "ex3.h"
#include "CommandTypes.h"
#include "Singleton.h"
#include <iostream>

unsigned LoopCommand::execute(vector<string>::iterator it) {
  cout << "in while loop" << endl;
  Singleton *s = Singleton::getInstance();
    this->makeCommandsList(it);
    string condition_str;
    unsigned currentIndex = 0;
    auto temp_it = it;


    while (*(temp_it + 1) != "{") {
        condition_str.append(*(temp_it + 1));
        ++temp_it;
    }
    temp_it += 2;

  auto temp_new = temp_it;
  int sub = 0, flag = 0, c = 0;
    while (parseCondition(condition_str)) {
      flag = 1;
        for (auto list_itr = this->m_commands_list.begin(); list_itr != this->m_commands_list.end(); ++list_itr) {
            Command *c = *(list_itr);
          currentIndex = c->execute(temp_it);
            temp_it += (currentIndex + 1);
        }

      sub = temp_it - temp_new;
      temp_it = temp_new;

    }
  temp_it += sub;
  if (flag == 1) {
    return temp_it - it;
  } else {
    while (*it != "}") {
      ++it;
      c++;
    }
    return c;
  }
}




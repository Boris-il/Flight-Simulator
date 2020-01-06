//
// Created by boris on 25/12/2019.
//

#include <iostream>
#include <algorithm>
#include "CommandTypes.h"
#include "Singleton.h"

using namespace std;

unsigned PrintCommand::execute(vector<string>::iterator it) {
    Singleton *s = Singleton::getInstance();
    Expression *e = nullptr;

    if (*it == "@") {
        ++it;
    }

    string val_as_string = *(it + 1);
    if (val_as_string.at(0) == '"') {
      string::iterator end_pos = remove(val_as_string.begin(), val_as_string.end(), '"');
      val_as_string.erase(end_pos, val_as_string.end());
        cout << val_as_string << endl;
    } else {
        try {
            // remove spaces
            string::iterator end_pos = remove(val_as_string.begin(), val_as_string.end(), ' ');
            val_as_string.erase(end_pos, val_as_string.end());
            val_as_string.erase(std::remove(val_as_string.begin(), val_as_string.end(), '\t'), val_as_string.end());

            // interpret
            e = s->m_inter->interpret(val_as_string);
            cout << e->calculate() << endl;
        } catch (const char *ex) {
            cerr << "error: could not interpret " << val_as_string << " in Print()" << endl;
        }
    }
    return 1;

}

//
// Created by boris on 25/12/2019.
//

#include "CommandTypes.h"
#include "ex1.h"
#include "ex3.h"
#include "Singleton.h"
#include <iostream>
#include <algorithm>

bool ConditionParser::parseCondition(const string &str) {
    Singleton *s = Singleton::getInstance();
    Expression *e1 = nullptr, *e2 = nullptr;
    string sub_left, sub_right, sub_op;
    size_t pos = 0;

    // lexer for the condition string. for each mathematical operator, returns the final calculation.
    pos = str.find("<=");
    if (pos == string::npos) {
        pos = str.find(">=");
        if (pos == string::npos) {
            pos = str.find("==");
            if (pos == string::npos) {
                pos = str.find("!=");
                if (pos == string::npos) {
                    pos = str.find('<');
                    if (pos == string::npos) {
                        pos = str.find('>');
                        if (pos == string::npos) {
                            cerr << "bad condition operator" << endl;
                        } else {
                            sub_left = str.substr(0, pos);
                            sub_right = str.substr(pos + 1, str.length() - pos);
                            e1 = s->m_inter->interpret(sub_left);
                            e2 = s->m_inter->interpret(sub_right);
                            return e1->calculate() > e2->calculate();
                        }
                    } else {
                        sub_left = str.substr(0, pos);
                        sub_right = str.substr(pos + 1, str.length() - pos);
                        e1 = s->m_inter->interpret(sub_left);
                        e2 = s->m_inter->interpret(sub_right);
                        return e1->calculate() < e2->calculate();
                    }
                } else {
                    sub_left = str.substr(0, pos);
                    sub_right = str.substr(pos + 2, str.length() - (pos + 1));
                    e1 = s->m_inter->interpret(sub_left);
                    e2 = s->m_inter->interpret(sub_right);
                    return e1->calculate() != e2->calculate();
                }
            } else {
                sub_left = str.substr(0, pos);
                sub_right = str.substr(pos + 2, str.length() - (pos + 1));
                e1 = s->m_inter->interpret(sub_left);
                e2 = s->m_inter->interpret(sub_right);
                return e1->calculate() == e2->calculate();
            }
        } else {
            sub_left = str.substr(0, pos);
            sub_right = str.substr(pos + 2, str.length() - (pos + 1));
            e1 = s->m_inter->interpret(sub_left);
            e2 = s->m_inter->interpret(sub_right);
            return e1->calculate() >= e2->calculate();
        }
    } else {
        sub_left = str.substr(0, pos);
        sub_right = str.substr(pos + 2, str.length() - (pos + 1));
        e1 = s->m_inter->interpret(sub_left);
        e2 = s->m_inter->interpret(sub_right);
        return e1->calculate() <= e2->calculate();
    }
    return false;
}

void ConditionParser::makeCommandsList(vector<string>::iterator it) {
    Singleton *s = Singleton::getInstance();

    while (*it != "}") {
        if (*it == "@") {
            // string of the command
            string com = *(it + 1);
            // erase tabs and spaces from the string
            com.erase(std::remove(com.begin(), com.end(), '\t'), com.end());
            string::iterator end_pos = remove(com.begin(), com.end(), ' ');
            com.erase(end_pos, com.end());
            // search for the command in commands map
            auto cmd_map_it = s->m_commands_map.find(com);
            if (cmd_map_it != s->m_commands_map.end()) {
                Command *c = cmd_map_it->second;
                // once found, push to commands list
                this->m_commands_list.push_back(c);

            } else {
                try {
                    // if no command found, check if the variable is known
                    double val = s->m_inter->getVarValue(*(it + 1));
                    // once the variable found, add DefineVar command to the list
                    auto cmd_map_it = s->m_commands_map.find("var");
                    Command *c = cmd_map_it->second;
                    this->m_commands_list.push_back(c);
                } catch (const char *e) {
                    cerr << "unknown command" << endl;
                }
            }
        }
        ++it;
    }
}

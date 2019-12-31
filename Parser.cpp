//
// Created by boris on 20/12/2019.
//


#include "ex3.h"
#include "CommandTypes.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Singleton.h"

using namespace std;

// implement lexer
vector<string> Parser::lexer(const string &fileName) {
    string line, sub_command, sub_value;
    size_t pos = 0, pos_temp = 0;
    fstream in_file;
    vector<string> ret_string;
    bool condition_scope = false;
    in_file.open(fileName, ios::in);
    if (!in_file.is_open()) {
        cerr << "File open error" << endl;
    } else {

        // lexer for the fly.txt file
        while (getline(in_file, line)) {

            if (condition_scope && line.find('}') == string::npos) {
                ret_string.push_back("@");
            }

            if (line.find("Print") == string::npos) {
                // remove all spaces from the line
                string::iterator end_pos = remove(line.begin(), line.end(), ' ');
                line.erase(end_pos, line.end());
                // remove tab from line
                line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            }

            // parse the line
            if (line.find('}') != string::npos) {
                ret_string.push_back("}");
                condition_scope = false;
                continue;
            }

            if (line.find("while") != string::npos) {
                condition_scope = true;
                // add the "while"
                ret_string.push_back(line.substr(0, 5));
                pos = line.find("<=");
                if (pos != string::npos) {
                    ret_string.push_back(line.substr(5, pos - 5));
                    ret_string.push_back("<=");
                    ret_string.push_back(line.substr(pos + 2, (line.length() - 1) - (pos + 2)));
                } else {
                    pos = line.find("=>");
                    if (pos != string::npos) {
                        ret_string.push_back(line.substr(5, pos - 5));
                        ret_string.push_back("=>");
                        ret_string.push_back(line.substr(pos + 2, (line.length() - 1) - (pos + 2)));
                    } else {
                        pos = line.find("==");
                        if (pos != string::npos) {
                            ret_string.push_back(line.substr(5, pos - 5));
                            ret_string.push_back("==");
                            ret_string.push_back(line.substr(pos + 2, (line.length() - 1) - (pos + 2)));

                        } else {
                            pos = line.find('>');
                            if (pos != string::npos) {
                                ret_string.push_back(line.substr(5, pos - 5));
                                ret_string.push_back(">");
                                ret_string.push_back(line.substr(pos + 1, (line.length() - 1) - (pos + 1)));
                            } else {
                                pos = line.find('<');
                                if (pos != string::npos) {
                                    ret_string.push_back(line.substr(5, pos - 5));
                                    ret_string.push_back("<");
                                    ret_string.push_back(line.substr(pos + 1, (line.length() - 1) - (pos + 1)));
                                }
                            }
                        }
                    }
                }
                ret_string.push_back("{");
                continue;
            }

            pos = line.find("var");
            if (pos != string::npos) {
                // add the "var"
                ret_string.push_back(line.substr(0, 3));
                pos_temp = line.find('=');
                if (pos_temp != string::npos) {
                    ret_string.push_back(line.substr(pos + 3, (pos_temp - (pos + 3))));
                    ret_string.push_back("=");
                    sub_value = line.substr(pos_temp + 1, (line.length() - 1) - (pos_temp));
                    ret_string.push_back(sub_value);
                    continue;
                }
                pos = line.find("<-");
                pos_temp = line.find("->");
                if (pos != string::npos || pos_temp != string::npos) {
                    if (pos_temp != string::npos) {
                        pos = pos_temp;
                    }
                    sub_command = line.substr(3, pos - 3);
                    ret_string.push_back(sub_command);
                    // append the arrow
                    ret_string.push_back(line.substr(pos, 2));
                    // append the "sim"
                    ret_string.push_back(line.substr(pos + 2, 3));
                    sub_value = line.substr(pos + 6, (line.length() - 1) - (pos + 6));
                    ret_string.push_back(sub_value);
                    continue;
                }
            }

            pos = line.find('=');
            if (pos != string::npos) {
                sub_command = line.substr(0, pos);
                ret_string.push_back(sub_command);
                ret_string.push_back("=");
                sub_value = line.substr(pos + 1, line.length() - 1 - pos);
                ret_string.push_back(sub_value);
                continue;
            }

            pos = line.find('(');
            if (pos != string::npos) {
                sub_command = line.substr(0, pos);
                ret_string.push_back(sub_command);
                sub_value = line.substr(pos + 1, (line.length() - 1) - (pos + 1));
                ret_string.push_back(sub_value);
                continue;
            }
        }
    }
    return ret_string;
}

// implement parser
void Parser::parse(vector<string> &commands, map<string, Command *> cmdMap) {
    Singleton *s = Singleton::getInstance();
    map<string, Command *> cmd_map = (s->m_commands_map);

    // iteration over each line of commands in fly.txt and executing them
    auto itStart = commands.begin();
    unsigned currentIndex = 0;
    for (unsigned i = 0; i < commands.size(); i++) {
        auto pos = cmd_map.find(commands[i]);
        if (pos != cmd_map.end()) {
            Command *c = pos->second;
            currentIndex = c->execute(itStart + i);
            i += currentIndex;
            continue;
        } else {
            // if command is not defined, check if the variable already exists and execute DefineVarCommand
            auto pos1 = s->var_map.find(commands[i]);
            if (pos1 != s->var_map.end()) {
                Command *c = cmd_map["var"];
                currentIndex = c->execute(itStart + i - 1);
                i += (currentIndex - 1);
                continue;
            }

            cout << commands[i] << endl;
            cerr << "undefined command" << endl;

        }
    }
}




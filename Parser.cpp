//
// Created by boris on 20/12/2019.
//


#include "ex3.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// implement parser constructor
Parser::Parser() {
    // here I will initialize maps
}

// implement lexer
vector<string> Parser::lexer(string fileName) {
    string line, sub_command, sub_value;
    size_t pos = 0, pos_temp = 0;
    fstream in_file;
    vector<string> ret_string;
    in_file.open(fileName, ios::in);
    if (!in_file.is_open()) {
        cerr << "File open error" << endl;
    } else {
        while (getline(in_file, line)) {

            if (line.find("Print") == string::npos) {
                // remove all spaces from the line
                string::iterator end_pos = remove(line.begin(), line.end(), ' ');
                line.erase(end_pos, line.end());
                cout << line << endl;
            }

            // parse the line
            if (line.find('}') != string::npos) {
                ret_string.push_back("}");
                ret_string.push_back(",");
                continue;
            }

            if (line.find("while") != string::npos) {
                // add the "while"
                ret_string.push_back(line.substr(0, 5));
                ret_string.push_back(",");
                pos = line.find('<');
                if (pos != string::npos) {
                    ret_string.push_back(line.substr(5, pos - 5));
                    ret_string.push_back(",");
                    ret_string.push_back("<");
                    ret_string.push_back(",");
                    ret_string.push_back(line.substr(pos + 1, (line.length() - 1) - (pos + 1)));
                } else {
                    pos = line.find('>');
                    if (pos != string::npos) {
                        ret_string.push_back(line.substr(5, pos - 5));
                        ret_string.push_back(",");
                        ret_string.push_back(">");
                        ret_string.push_back(",");
                        ret_string.push_back(line.substr(pos + 1, (line.length() - 1) - (pos + 1)));

                    } else {
                        pos = line.find("==");
                        if (pos != string::npos) {
                            ret_string.push_back(line.substr(5, pos - 5));
                            ret_string.push_back(",");
                            ret_string.push_back("==");
                            ret_string.push_back(",");
                            ret_string.push_back(line.substr(pos + 2, (line.length() - 1) - (pos + 2)));

                        } else {
                            pos = line.find("=>");
                            if (pos != string::npos) {
                                ret_string.push_back(line.substr(5, pos - 5));
                                ret_string.push_back(",");
                                ret_string.push_back("=>");
                                ret_string.push_back(",");
                                ret_string.push_back(line.substr(pos + 2, (line.length() - 1) - (pos + 2)));
                            } else {
                                pos = line.find("<=");
                                if (pos != string::npos) {
                                    ret_string.push_back(line.substr(5, pos - 5));
                                    ret_string.push_back(",");
                                    ret_string.push_back("<=");
                                    ret_string.push_back(",");
                                    ret_string.push_back(line.substr(pos + 2, (line.length() - 1) - (pos + 2)));
                                }
                            }
                        }
                    }
                }
                ret_string.push_back(",");
                ret_string.push_back("{");
                ret_string.push_back(",");
                continue;
            }

            pos = line.find("var");
            if (pos != string::npos) {
                // add the "var"
                ret_string.push_back(line.substr(0, 3));
                ret_string.push_back(",");
                pos_temp = line.find('=');
                if (pos_temp != string::npos) {
                    ret_string.push_back(line.substr(pos + 3, (pos_temp - (pos + 3))));
                    ret_string.push_back(",");
                    ret_string.push_back("=");
                    ret_string.push_back(",");
                    sub_value = line.substr(pos_temp + 1, (line.length() - 1) - (pos_temp));
                    ret_string.push_back(sub_value);
                    ret_string.push_back(",");
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
                    ret_string.push_back(",");
                    // append the arrow
                    ret_string.push_back(line.substr(pos, 2));
                    ret_string.push_back(",");
                    // append the "sim"
                    ret_string.push_back(line.substr(pos + 2, 3));
                    ret_string.push_back(",");
                    sub_value = line.substr(pos + 6, (line.length() - 1) - (pos + 6));
                    ret_string.push_back(sub_value);
                    ret_string.push_back(",");
                    continue;
                }
            }

            pos = line.find('=');
            if (pos != string::npos) {
                sub_command = line.substr(0, pos);
                ret_string.push_back(sub_command);
                ret_string.push_back(",");
                ret_string.push_back("=");
                sub_value = line.substr(pos + 1, line.length() - 1 - pos);
                ret_string.push_back(sub_value);
                ret_string.push_back(",");
                continue;
            }

            pos = line.find('(');
            if (pos != string::npos) {
                sub_command = line.substr(0, pos);
                ret_string.push_back(sub_command);
                ret_string.push_back(",");
                sub_value = line.substr(pos + 1, (line.length() - 1) - (pos + 1));
                ret_string.push_back(sub_value);
                ret_string.push_back(",");
                continue;
            }
        }
    }
    return ret_string;
}

// implement parser



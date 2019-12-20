//
// Created by boris on 20/12/2019.
//

#ifndef FLIGHT_SIMULATOR_EX3_H
#define FLIGHT_SIMULATOR_EX3_H


#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Parser {
    //unordered_map<string, Command> commands_map;

public:
    // constructor
    Parser();

    // destructor
    ~Parser() {};

    // lexer func declaration
    vector<string> lexer(string);

    // parse func declaration

};

#endif //FLIGHT_SIMULATOR_EX3_H

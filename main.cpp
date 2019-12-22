#include <iostream>
#include <vector>
#include <algorithm>
#include "CommandTypes.h"

using namespace std;

int main(int argc, char *argv[]) {
    Parser p;
    // commands map
    map<string, Command *> cmd_map;
    DefineVarCommand def = DefineVarCommand();
    cmd_map["var"] = &def;


    vector<string> commands;
    // get array of commands and their arguments
    commands = p.lexer(argv[1]);
    p.parse(commands, cmd_map);

    std::cout << "Hello, World!" << std::endl;

    // unsigned d = OpenServerCommand("5400").execute(p.cmd_map, p.var_map);
    // d=ConnectCommand("127.0.0.1", "5402").execute();
    cout << "finished" << endl;
    return 0;
}
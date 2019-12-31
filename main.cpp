#include <iostream>
#include <vector>
#include <algorithm>
#include "CommandTypes.h"
#include <thread>
#include "ex3.h"

int main(int argc, char *argv[]) {
    // Singleton class according to Singleton design pattern. It stores maps and other conditional members.
    Singleton *s = Singleton::getInstance();

    Parser p;
    // commands map
    map<string, Command *> cmd_map;
    // commands vector from fly.txt
    vector<string> commands_from_lexer;
    // get array of commands and their arguments
    commands_from_lexer = Parser::lexer(argv[1]);
    // parse the commands vector
    p.parse(commands_from_lexer, cmd_map);

    return 0;
}

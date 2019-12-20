#include <iostream>
#include <vector>
#include <algorithm>
#include "CommandTypes.h"

using namespace std;

int main(int argc, char *argv[]) {
    Parser p;
    vector<string> commands;
    // get array of commands and their arguments
    commands = p.lexer(argv[1]);
    p.parse(commands);

    std::cout << "Hello, World!" << std::endl;

    double d = OpenServerCommand("5400").execute();
    // d=ConnectCommand("127.0.0.1", "5402").execute();
    cout << "finished" << endl;
    return 0;
}
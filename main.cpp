#include <iostream>
#include <vector>
#include <algorithm>
#include "CommandTypes.h"
#include <thread>

using namespace std;
void func1();
void func2();
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

    thread t1(func1);
//    double d = OpenServerCommand("5400").execute();
  thread t2(func2);
   // d=ConnectCommand("127.0.0.1", "5400").execute();
  t1.join();
  t2.join();
    cout << "finished" << endl;

    return 0;
}

void func1(){
  OpenServerCommand  *osc= new OpenServerCommand("5400");
  osc->execute();
}

void func2 (){
  ConnectCommand  *cc= new ConnectCommand("127.0.0.1", "5400");
  cc->execute();
}
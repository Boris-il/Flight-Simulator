#include <iostream>
#include <vector>
#include <algorithm>
#include "CommandTypes.h"
#include <thread>
#include "ex3.h"

using namespace std;

//static void populateCommandsMap(vector<string> *commands_from_lexer, map<string, Command *> *cmd_map) {
//    // create each command and insert to map
//    DefineVarCommand def = DefineVarCommand(commands_from_lexer);
//    (*cmd_map)["var"] = &def;
//}

void func1();

void func2();

int main(int argc, char *argv[]) {
    Parser p;
    // commands map
    map<string, Command *> cmd_map;
    // commands vector from fly.txt
    vector<string> commands_from_lexer;
    // get array of commands and their arguments
    commands_from_lexer = Parser::lexer(argv[1]);

    // build commands map
//    populateCommandsMap(&commands_from_lexer, &cmd_map);
    DefineVarCommand def = DefineVarCommand();
    cmd_map["var"] = &def;
    ConnectCommand cnt = ConnectCommand();
    cmd_map["connectControlClient"] = &cnt;
    OpenServerCommand opn = OpenServerCommand();
    cmd_map["openDataServer"] = &opn;
    SleepCommand slp = SleepCommand();
    cmd_map["Sleep"] = &slp;
    PrintCommand prt = PrintCommand();
    cmd_map["Print"] = &prt;
    LoopCommand whl = LoopCommand();
    cmd_map["while"] = &whl;

    // parse the commands vector
    p.parse(commands_from_lexer, cmd_map);

//    thread t1(func1);
//    double d = OpenServerCommand("5400").execute();
//    thread t2(func2);
    // d=ConnectCommand("127.0.0.1", "5400").execute();
//    t1.join();
//    t2.join();
    cout << "finished" << endl;

    return 0;
}

//void func1(){
//  OpenServerCommand  *osc= new OpenServerCommand("5400");
//  osc->execute();
//}
//
//void func2 (){
//  ConnectCommand  *cc= new ConnectCommand("127.0.0.1", "5400");
//  cc->execute();
//}
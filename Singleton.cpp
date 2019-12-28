//
// Created by boris on 24/12/2019.
//

#include "Singleton.h"
#include "CommandTypes.h"
#include <map>
#include "ex3.h"

Singleton *Singleton::instance = nullptr;

Singleton *Singleton::getInstance() {
    if (instance == nullptr) {
        instance = new Singleton();
    }
    return instance;
}

Singleton::Singleton() {
    this->m_inter = new Interpreter();

    Command *def = new DefineVarCommand();
    this->m_commands_map["var"] = def;
    Command *cnt = new ConnectCommand();
    this->m_commands_map["connectControlClient"] = cnt;
    Command *opn = new OpenServerCommand();
    this->m_commands_map["openDataServer"] = opn;
    Command *slp = new SleepCommand();
    this->m_commands_map["Sleep"] = slp;
    Command *prt = new PrintCommand();
    this->m_commands_map["Print"] = prt;
    Command *loop = new LoopCommand();
    this->m_commands_map["while"] = loop;
}

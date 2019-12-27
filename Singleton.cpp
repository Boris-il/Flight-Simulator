//
// Created by boris on 24/12/2019.
//

#include "Singleton.h"

Singleton *Singleton::instance = nullptr;

Singleton *Singleton::getInstance() {
    if (instance == nullptr) {
        instance = new Singleton();
    }
    return instance;
}

Singleton::Singleton() {
    this->m_inter = new Interpreter();
}

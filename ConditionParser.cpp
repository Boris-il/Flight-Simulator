//
// Created by boris on 25/12/2019.
//

#include "CommandTypes.h"
#include "ex3.h"

void ConditionParser::addChild(Command *c) {
    this->m_commands_list.push_back(c);
}

bool ConditionParser::parseCondition(const string &condition) {

}

void ConditionParser::makeCommandsList(vector<string>::iterator) {

}
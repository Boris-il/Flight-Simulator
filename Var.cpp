//
// Created by boris on 22/12/2019.
//

#include "ex3.h"

Var::Var(string var_name, bool isBound, unsigned bound_type, string simPath) {
    this->m_var_name = var_name;
    this->m_isBound = isBound;
    this->m_bound_type = bound_type;
    this->m_simPath = simPath;
}

Var::Var(string var_name, unsigned scope, Var *v) {
    this->m_var_name = var_name;
    this->m_scope = scope;
    this->m_bound_type = v->m_bound_type;
}

bool Var::operator==(const Var &v) const {
    return (this->m_var_name == v.m_var_name);
}

void Var::setValue(double num) {
    this->value = num;
}
string Var::getSim() {
  return this->m_simPath;
}
double Var::getValue() {
  return this->value;
}

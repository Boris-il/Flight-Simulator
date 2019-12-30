//
// Created by boris on 20/12/2019.
//

#include <iostream>

#include "ex1.h"

#include<string>

using namespace std;

Variable::Variable(string str, double val) {
    this->name = str;
    this->value = val;
}

// define getters
string Variable::getName() const {
    return this->name;
}

double Variable::getValue() const {
    return this->value;
}

// define prefix increment(++) operator
Variable &Variable::operator++() {
    (this->value)++;
    return *this;
}

// define postfix increment(++) operator
Variable &Variable::operator++(int) {
    ++*this;
    return *this;
}

// define prefix decrement operator
Variable &Variable::operator--() {
    value--;
    return *this;
}

// define postfix decrement operator
Variable &Variable::operator--(int) {
    --*this;
    return *this;
}

// define += operator
Variable &Variable::operator+=(double val) {
    this->value += val;
    return *this;
}

// define -= operator
Variable &Variable::operator-=(double val) {
    this->value -= val;
    return *this;
}

// define calculate
double Variable::calculate() {
    return this->value;
}

// define Value constructor
Value::Value(double v) {
    this->val = v;
}

// define Value calculate
double Value::calculate() {
    return this->val;
}

// Plus constructor
Plus::Plus(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

// define Plus calculate
double Plus::calculate() {
    return (this->left->calculate() + this->right->calculate());
}

// Minus constructor
Minus::Minus(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

// define Minus calculate
double Minus::calculate() {
    return (this->left->calculate() - this->right->calculate());
}

// Mul constructor
Mul::Mul(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

// define Mul calculate
double Mul::calculate() {
    return (this->left->calculate() * this->right->calculate());
}

// Div constructor
Div::Div(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

// define Div calculate
double Div::calculate() {
  if (this->getRight()->calculate() == 0) {
        throw "bad input";
    } else {
        return ((this->getLeft()->calculate()) / (this->getRight()->calculate()));
    }
}

// define UnaryExpression getter
Expression *UnaryOperator::getUnaryExpression() {
    return this->unaryExp;
}

// define UPlus constructor
UPlus::UPlus(Expression *exp) {
    this->unaryExp = exp;
}

// define UPlus calculate
double UPlus::calculate() {
    return (this->unaryExp->calculate());
}

// define UMinus constructor
UMinus::UMinus(Expression *exp) {
    this->unaryExp = exp;
}

// define UMinus calculate
double UMinus::calculate() {
    return ((this->unaryExp->calculate()) * (-1));
}


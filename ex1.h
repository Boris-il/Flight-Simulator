//
// Created by boris on 20/12/2019.
//

#ifndef FLIGHT_SIMULATOR_EX1_H
#define FLIGHT_SIMULATOR_EX1_H

#include "Expression.h"

#include <string>
#include <stack>
#include <queue>
#include <map>

using namespace std;

class Variable : public Expression {
private:
    string name;
    double value;

public:
    // declare constructor
    Variable(string name, double val);

    // declare destructor
    ~Variable() {
    };

    // getters
    string getName() const;

    double getValue() const;

    // declare prefix and postfix increment operators
    Variable &operator++();

    Variable &operator++(int);

    // declare prefix and postfix decrement operators
    Variable &operator--();

    Variable &operator--(int);

    // declare += operator
    Variable &operator+=(double val);

    // declare -= operator
    Variable &operator-=(double val);

    // declare calculate
    double calculate() override;
};

class Value : public Expression {
private:
    double val;

public:
    // constructor
    Value(double v);

    // destructor
    ~Value() {};

    // getter
    double getValue() const { return this->val; }

    // declare Value calculate
    double calculate() override;
};

class BinaryOperator : public Expression {
protected:
    Expression *left = nullptr;
    Expression *right = nullptr;

public:
    // destructor
    virtual ~BinaryOperator() {
        if (this->left != nullptr) {
            delete this->left;
        }
        if (this->right != nullptr) {
            delete this->right;
        }
    }

    // getters
    Expression *getLeft() const {
        return this->left;
    }

    Expression *getRight() const {
        return this->right;
    }
};

class Plus : public BinaryOperator {
public:
    // constructor
    Plus(Expression *left, Expression *right);

    // destructor
    ~Plus() {};

    // declare calculate
    double calculate() override;
};

class Minus : public BinaryOperator {
public:
    // constructor
    Minus(Expression *left, Expression *right);

    // destructor
    ~Minus() {};

    // calculate declaration
    double calculate() override;
};

class Mul : public BinaryOperator {
public:
    // constructor
    Mul(Expression *l, Expression *r);

    // destructor
    ~Mul() {};

    // declare calculate
    double calculate() override;
};

class Div : public BinaryOperator {
public:
    // constructor
    Div(Expression *l, Expression *r);

    // destructor
    ~Div() {
    };

    // declare calculate
    double calculate() override;
};

class UnaryOperator : public Expression {
protected:
    Expression *unaryExp;

public:
    // destructor
    virtual ~UnaryOperator() {
        if (this->unaryExp != nullptr) {
            delete this->unaryExp;
        }
    };

    Expression *getUnaryExpression();
};

class UPlus : public UnaryOperator {
public:
    // declare constructor
    UPlus(Expression *exp);

    // destructor
    ~UPlus() {
    };

    // declare getter
    Expression *getLeft() const {
        return this->unaryExp;
    }

    // declare UPlus calculate
    double calculate() override;
};

class UMinus : public UnaryOperator {
public:
    // declare constructor
    UMinus(Expression *exp);

    // destructor
    ~UMinus() {
    };

    // declare getter
    Expression *getLeft() const {
        return this->unaryExp;
    }

    // declare UMinus calculate
    double calculate() override;
};

class Interpreter {
private:
    // declare a stack for infix-postfix operators
    stack<string> opStack;
    // declare a queue for postfix result
    queue<string> postfix;
    // declare a map for variables and their values
    map<string, double> variablesMap;
    // stack for expressions
    stack<Expression *> expStack;

    bool isVariable(char c);

    bool isOperator(char c);

    bool isNumber(char c);

    bool isLetter(char c);

    int getPriority(char op);

    void parseVariable(string var);

    bool validVarName(string input);

    string getComponent(int pos, string s);

    double getVarValue(string var);

    void infixToPostfix(string input);

    bool isNumVal(string s);

public:
    // constructor
    Interpreter() {};

    // destructor
    ~Interpreter() {};

    void setVariables(string input);

    Expression *interpret(string input);
};


#endif //FLIGHT_SIMULATOR_EX1_H

//
// Created by boris on 20/12/2019.
//

#include "ex1.h"
#include <iostream>
#include <string>
#include <map>
#include <cstring>

using namespace std;

Expression *Interpreter::interpret(string input) {
    string tempElement;
    char op;
    Expression *tempExp = nullptr, *tempRightExp = nullptr, *tempLeftExp = nullptr;
    // translate unary to binary
    size_t pos = 0;

    string input1 = "(" + input + ")";
    while ((pos = input1.find("(-")) != string::npos) {
        input1.replace(pos, 1, "(0");
    }

    // translate input to postfix notation
    infixToPostfix(input1);
    // insert each element of the postfix queue into Expressions stack
    while (!this->postfix.empty()) {
        tempElement = this->postfix.front();
        if (!isOperator(tempElement[0])) {
            if (isNumVal(tempElement)) {
                tempExp = new Value(stod(tempElement));
            } else {
                tempExp = new Variable(tempElement, getVarValue(tempElement));
            }
            this->expStack.push(tempExp);
        } else {
            // else it's an operator
            op = tempElement[0];
            tempRightExp = this->expStack.top();
            this->expStack.pop();
            tempLeftExp = this->expStack.top();
            this->expStack.pop();
            // which operator?
            switch (op) {
                case '+':tempExp = new Plus(tempLeftExp, tempRightExp);
                    break;
                case '-':tempExp = new Minus(tempLeftExp, tempRightExp);
                    break;
                case '*':tempExp = new Mul(tempLeftExp, tempRightExp);
                    break;
                case '/':tempExp = new Div(tempLeftExp, tempRightExp);
                default:break;
            }
            // push new Expression to stack
            this->expStack.push(tempExp);
        }
        // remove element from queue
        this->postfix.pop();
    }
    return this->expStack.top();
}

double Interpreter::getVarValue(string var) {
    // create map iterator
    map<string, double>::iterator it;

    // find value of the given key
    it = this->variablesMap.find(var);
    if (it != this->variablesMap.end()) {
        return it->second;
    } else {
        throw "bad input";
    }
}

void Interpreter::setVariables(string input) {
    string sub;
    int startIndex = 0;
    size_t pos = 0;
    // parse to substrings
    while (input.find(';', startIndex) != size_t(-1)) {
        pos = input.find(';', startIndex);
        sub = input.substr(startIndex, pos - startIndex);
        parseVariable(sub);
        startIndex = pos + 1;
    }
    sub = input.substr(startIndex, input.length() - startIndex);
    parseVariable(sub);
}

void Interpreter::parseVariable(string input) {
    string var, val;
    // create map iterator
    map<string, double>::iterator it;
    double value = 0;
    int pos = input.find('=');
    if (pos == -1) {
        throw "bad input";
    } else {
        var = input.substr(0, pos);
        if (!(validVarName(var))) {
            throw "bad input";
        }
        val = input.substr(pos + 1, input.length() - 1);

        if (!isNumVal(val)) {
            throw "bad input";
        } else {
            value = stod(val);
        }
    }
    // check if key already exists. If yes, delete it
    it = this->variablesMap.find(var);
    if (it != this->variablesMap.end()) {
        this->variablesMap.erase(it);
    }
    // add the variable and its value to the map
    this->variablesMap.insert({var, value});
}

void Interpreter::infixToPostfix(string input) {
    string sub, temp;
    string currentTop;
    // create map iterator
    map<string, double>::iterator it;
    // iterate each char in string
    for (unsigned int i = 0; i < input.length(); i++) {
        // check if operator
        if (isOperator(input[i])) {
            if (!this->opStack.empty()) {
                currentTop = this->opStack.top();
                if (isOperator(currentTop[0]) && getPriority(currentTop[0]) >= getPriority(input[i])) {
                    this->postfix.push(this->opStack.top());
                    this->opStack.pop();
                }
            }
            temp = input[i];
            this->opStack.push(temp);
            continue;
        }
        // left bracket always goes to stack
        if (input[i] == '(') {
            temp = input[i];
            this->opStack.push(temp);
            continue;
        }

        // right bracket pushes everything from stack to queue until left bracket is in top on stack
        if (input[i] == ')') {
            string top = this->opStack.top();
            while (top[0] != '(') {
                this->postfix.push(this->opStack.top());
                this->opStack.pop();
                top = this->opStack.top();
            }
            // pop the '(' that remains
            this->opStack.pop();
            continue;
        }

        sub = getComponent(i, input);
        // check if component is a variable
        it = this->variablesMap.find(sub);
        if (it != this->variablesMap.end()) {
            this->postfix.push(sub);
        } else if (isNumVal(sub)) {
            this->postfix.push(sub);
        } else {
            throw "bad input";
        }
        // fix index
        i += (sub.length() - 1);
    }

    //push remaining chars in stack to queue
    while (!this->opStack.empty()) {
        this->postfix.push(this->opStack.top());
        this->opStack.pop();
    }
}

bool Interpreter::isNumVal(string s) {
    if (s.compare("-") == 0) {
        return false;
    }
    int count = 0;
    for (unsigned int i = 0; i < s.length(); ++i) {
        if (s[i] == '.') {
            count++;
        }
        if ((s[i] == '-') && (i != 0)) {
            return false;
        }
    }
    return (strspn(s.c_str(), ".0123456789-") == s.size() && count <= 1);


//    int dotCount = 0;
//    for (unsigned int j = 0; j < s.length(); j++) {
//        if (!isNumber(s[j])) {
//            if (s[j] == '.') {
//                dotCount++;
//            } else {
//                return false;
//            }
//        }
//        if (dotCount > 1) {
//            return false;
//        }
//    }
//    return true;
}

string Interpreter::getComponent(int pos, string s) {
    int posTemp = pos;
    string comp;
    for (unsigned int i = posTemp; i <= s.length(); i++) {
        if (isOperator(s[posTemp]) || s[posTemp] == '(' || s[posTemp] == ')' || i == s.length()) {
            comp = s.substr(pos, posTemp - pos);
            break;
        }
        posTemp++;
    }
    return comp;
}

bool Interpreter::isNumber(char c) {
    return c >= '0' && c <= '9';
}

bool Interpreter::validVarName(string s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        if (i == 0) {
            if (!isLetter(s[i]) && s[i] != '_') {
                return false;
            }
        } else if (!((isLetter(s[i]) || isNumber(s[i]) || s[i] == '_'))) {
            return false;
        }
    }
    return true;
}

bool Interpreter::isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Interpreter::isVariable(char c) {
    // if number
    if (c >= '0' && c <= '9') {
        return true;
    }
    // if small letter
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    // if big letter
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}

bool Interpreter::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int Interpreter::getPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    // else if it's '*' or '/'
    return 2;
}

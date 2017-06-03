/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExpressionParser.h
 * Author: Zulfia Garifullina
 *
 * Created on 30 мая 2017 г., 14:08
 */

#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <algorithm>
#include <cfloat>
#include <iostream>
#include <iterator>
#include <list>
#include <math.h>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/*
 * Expression Parser is a parser for evaluating
 * arithmetic expressions input as a string.
 */
class ExpressionParser {

private:
    // Input expression written in infix notation.
    vector<string> inputExpression;
    // Output expression written in Reversed Polish Notation (RPN).
    vector<string> outputExpression;
    
    // Checks if a string element is a whitespace character.
    bool isWhitespace(const string & s);
    
    // Checks if a string element is an arithmetic operator.
    // It is assumed that four operators used here are all left-associative.
    bool isOperator(const string & s);
    
    // Checks if a string element is a digit.
    bool isDigit(const string & s);
    
    // Checks if a string element is a letter.
    bool isLetter(const string & s);
    
    // Checks if a string element is a left parenthesis.
    bool isLeftParenthesis(const string & s);
    
    // Checks if a string element is a right parenthesis.
    bool isRightParenthesis(const string & s);
    
    // Checks if a string element is a parenthesis.
    bool isParenthesis(const string & s);
    
    // Checks if a string element is not a valid character.
    bool isNotValid(const string & s);
    
    // Checks if a string element is a sign.
    // A sign here is a unary right-associative operator.
    bool isSign(const int & iter, const string & s1, const string & s2);
    
    // Compares precedence of operators o1 and o2.
    // Returns  1 if o1 has higher precedence than o2,
    // Returns -1 if o1 has lower or equal precedence to that of o2.
    int comparePrecedence (const string & o1, const string & o2);
     
    // Checks if operator o has low precedence: + or -.
    bool isLowPrecedence(const string & o);
    
    // Checks if operator o has high precedence: * or /.
    bool isHighPrecedence(const string & o);
    
public:
    // Default class constructor
    ExpressionParser();
      
    // Converts the expression written in infix notation to
    // Reverse Polish Notation using Shunting-yard algorithm.
    // Returns true if successful.
    bool convertToRPN(const string & infixInput);
    
    // Evaluates the expression written in RPN using a stack.
    // Returns evaluation result rounded to two digits after decimal point.
    double evaluateRPN();
};

#endif /* EXPRESSIONPARSER_H */


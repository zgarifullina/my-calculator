/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Zulfia Garifullina
 *
 * Created on 28 мая 2017 г., 12:31
 */
#include "ExpressionParser.h"
#include <cstdlib>
#include <iostream>

/*
 * 
 */
int main(int argc, char** argv) {

    ExpressionParser parser;
    cout << "Input the expression you want to calculate\n";
    for (string expressionString; getline(cin, expressionString);) {
        if (parser.convertToRPN(expressionString)) {
            if (!(parser.evaluateRPN() == DBL_MAX))
                cout << "Result:" << parser.evaluateRPN() << endl;
        }
        cout << "\nInput the expression you want to calculate\n";
    }
    return 0;
}


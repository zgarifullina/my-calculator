/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   evaluaterpnsimpletest.cpp
 * Author: Zulfia Garifullina
 *
 * Created on 3 июня 2017 г., 16:43
 */

#include <stdlib.h>
#include <iostream>
#include "ExpressionParser.h"

/*
 * Simple C++ Test Suite
 */

// Tests that the evaluation method returns correct results
void testEvaluateRPN() {
    const string& infixInput1 = "-1+5-4";
    const string& infixInput2 = "-10   + (8*2.5)- (3/1,5)";
    const string& infixInput3 = "1+(2*(2.5+2.5+(3-2)))-(3/1,5)";
    const string& infixInput4 = "(-(5*6)+2)/4 ";
    const string& infixInput5 = "(2+-3.4)*(5.4+6.80)-(2/+3)";
    ExpressionParser parser1;
    
    parser1.convertToRPN(infixInput1);
    double result1 = parser1.evaluateRPN();
    parser1.convertToRPN(infixInput2);
    double result2 = parser1.evaluateRPN();
    parser1.convertToRPN(infixInput3);
    double result3 = parser1.evaluateRPN();
    parser1.convertToRPN(infixInput4);
    double result4 = parser1.evaluateRPN();
    parser1.convertToRPN(infixInput5);
    double result5 = parser1.evaluateRPN();
    
    if ((result1 != 0) ||
        (result2 != 8) ||
        (result3 != 11) ||
        (result4 != -7) ||
        (result5 != -17.75)) {
        std::cout << "%TEST_FAILED% time=0 testname=testEvaluateRPN (evaluaterpnsimpletest) message=error message sample" << std::endl;
    }
}

// Tests that the evaluation method fails for incorrect expressions
void testFailedEvaluateRPN() {
    const string& infixInput1 = "0,3+4 5";
    const string& infixInput2 = "3.87 + 1/(5*)";
    const string& infixInput3 = "+";
    const string& infixInput4 = "(7 - 10) + 2.39 / 0";
    ExpressionParser parser2;
    
    parser2.convertToRPN(infixInput1);
    double result1 = parser2.evaluateRPN();
    parser2.convertToRPN(infixInput2);
    double result2 = parser2.evaluateRPN();
    parser2.convertToRPN(infixInput3);
    double result3 = parser2.evaluateRPN();
    parser2.convertToRPN(infixInput4);
    double result4 = parser2.evaluateRPN();
    
    if ((result1 != DBL_MAX) ||
        (result2 != DBL_MAX) ||
        (result3 != DBL_MAX) ||
        (result4 != DBL_MAX)) {
        std::cout << "%TEST_FAILED% time=0 testname=testEvaluateRPN (evaluaterpnsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% evaluaterpnsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testEvaluateRPN (evaluaterpnsimpletest)" << std::endl;
    testEvaluateRPN();
    std::cout << "%TEST_FINISHED% time=0 testEvaluateRPN (evaluaterpnsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testFailedEvaluateRPN (evaluaterpnsimpletest)" << std::endl;
    testFailedEvaluateRPN();
    std::cout << "%TEST_FINISHED% time=0 testFailedEvaluateRPN (evaluaterpnsimpletest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   converttorpnsimpletest.cpp
 * Author: Zulfia Garifullina
 *
 * Created on 3 июня 2017 г., 16:05
 */

#include <stdlib.h>
#include <iostream>
#include "ExpressionParser.h"

/*
 * Simple C++ Test Suite
 */

// Tests that the parsing method is successful for correct expressions
void testConvertToRPN() {
    const string& infixInput1 = "-1+5-4";
    const string& infixInput2 = "-10   + (8*2.5)- (3/1,5)";
    const string& infixInput3 = "1+(2*(2.5+2.5+(3-2)))-(3/1,5)";
    const string& infixInput4 = "(-(5*6)+2)/4 ";
    const string& infixInput5 = "(2+-3.4)*(5.4+6.80)-(2/+3)";
    ExpressionParser parser1;
    
    bool result1 = parser1.convertToRPN(infixInput1);
    bool result2 = parser1.convertToRPN(infixInput2);
    bool result3 = parser1.convertToRPN(infixInput3);
    bool result4 = parser1.convertToRPN(infixInput4);
    bool result5 = parser1.convertToRPN(infixInput5);
    
    if ((result1 == false) ||
        (result2 == false) ||
        (result3 == false) ||
        (result4 == false) ||
        (result5 == false)) {
        std::cout << "%TEST_FAILED% time=0 testname=testConvertToRPN (converttorpnsimpletest) message=error message sample" << std::endl;
    }
}

// Tests that the parsing method fails for incorrect expressions
void testFailedConvertToRPN() {
    const string& infixInput1 = "(1+2.67-(5,4*4-1)";
    const string& infixInput2 = "1+2.67)-(5,4*4-1)";
    const string& infixInput3 = "1.1+2.1+abc";
    const string& infixInput4 = "10.3+2=-4 ";
    const string& infixInput5 = " 10 .38+1";
    const string& infixInput6 = " 10. 38+1";
    const string& infixInput7 = "-10.3.8+1";
    const string& infixInput8 = " 10..38+1";
    const string& infixInput9 = "10.3845+1 ";
    const string& infixInput10 = "1+(5+6).";
    ExpressionParser parser2;
    
    bool result1 = parser2.convertToRPN(infixInput1);
    bool result2 = parser2.convertToRPN(infixInput2);
    bool result3 = parser2.convertToRPN(infixInput3);
    bool result4 = parser2.convertToRPN(infixInput4);
    bool result5 = parser2.convertToRPN(infixInput5);
    bool result6 = parser2.convertToRPN(infixInput6);
    bool result7 = parser2.convertToRPN(infixInput7);
    bool result8 = parser2.convertToRPN(infixInput8);
    bool result9 = parser2.convertToRPN(infixInput9);
    bool result10 = parser2.convertToRPN(infixInput10);
    
    if ((result1 == true) ||
        (result2 == true) ||
        (result3 == true) ||
        (result4 == true) ||
        (result5 == true) ||
        (result6 == true) ||
        (result7 == true) ||
        (result8 == true) ||
        (result9 == true) ||
        (result10 == true)) {
        std::cout << "%TEST_FAILED% time=0 testname=testFailedConvertToRPN (converttorpnsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% converttorpnsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testConvertToRPN (converttorpnsimpletest)" << std::endl;
    testConvertToRPN();
    std::cout << "%TEST_FINISHED% time=0 testConvertToRPN (converttorpnsimpletest)" << std::endl;
    
    std::cout << "%TEST_STARTED% testFailedConvertToRPN (converttorpnsimpletest)" << std::endl;
    testFailedConvertToRPN();
    std::cout << "%TEST_FINISHED% time=0 testFailedConvertToRPN (converttorpnsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}


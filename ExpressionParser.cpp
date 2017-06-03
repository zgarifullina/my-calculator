/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ExpressionParser.h"

// Default class constructor
ExpressionParser::ExpressionParser() {
}

    // Checks if a string element is a whitespace character.
    bool ExpressionParser::isWhitespace(const string & s) {
        return (s == " ");
    }
    
    // Checks if a string element is an arithmetic operator.
    // It is assumed that four operators used here are all left-associative.
    bool ExpressionParser::isOperator(const string & s) {
        return (s == "+") ||
               (s == "-") ||
               (s == "*") ||
               (s == "/");
    }
    
    // Checks if a string element is a digit.
    bool ExpressionParser::isDigit(const string & s) {
        return ("0" <= s) && (s <= "9");
    }
    
    // Checks if a string element is a letter.
    bool ExpressionParser::isLetter(const string & s) {
        return (("a" <= s) && (s <= "z")) || (("A" <= s) && (s <= "Z"));
    }
    
    // Checks if a string element is a left parenthesis.
    bool ExpressionParser::isLeftParenthesis(const string & s) {
        return (s == "(");
    }
    
    // Checks if a string element is a right parenthesis.
    bool ExpressionParser::isRightParenthesis(const string & s) {
        return (s == ")");
    }
    
    // Checks if a string element is a parenthesis.
    bool ExpressionParser::isParenthesis(const string & s) {
        return (s =="(") || (s == ")");
    }
    
    // Checks if a string element is not a valid character.
    bool ExpressionParser::isNotValid(const string & s) {
        return !isWhitespace(s) &&
                 !isOperator(s) &&
                    !isDigit(s) &&
                   !isLetter(s) &&
                     ("." != s);
    }
    
    // Checks if a string element is a sign.
    // A sign here is a unary right-associative operator.
    bool ExpressionParser::isSign(const int & iter, const string & s1, const string & s2) {
        // A sign is a right-associative operator, plus or minus,
        // followed by its operand, a number.
        // It can appear at the start of the expression,
        // after left parenthesis, or after left-associative operator.
        return (((iter == 0) || (s2 == "(") || (isOperator(s2))) &&
                ((s1 == "+") || (s1 == "-")));
    }
    
    // Compares precedence of operators o1 and o2.
    // Returns  1 if o1 has higher precedence than o2,
    // Returns -1 if o1 has lower or equal precedence to that of o2.
    int ExpressionParser::comparePrecedence (const string & o1, const string & o2) {
        if (isHighPrecedence(o2) ||
            (isLowPrecedence(o2) && isLowPrecedence(o1)))
            return -1;
        else return 1;
    }
    
    // Checks if operator o has low precedence: + or -.
    bool ExpressionParser::isLowPrecedence(const string & o) {
        return ((o == "+") || (o == "-"));
    }
    
    // Checks if operator o has high precedence: * or /.
    bool ExpressionParser::isHighPrecedence(const string & o) {
        return ((o == "*") || (o == "/"));
    }    
      
    // Converts the expression written in infix notation to
    // Reverse Polish Notation using Shunting-yard algorithm.
    // Returns true if successful.
    bool ExpressionParser::convertToRPN(const string & infixInput) {
        // Operator stack
        stack<string> operStack;
        // Number flag
        int number = 0;
        // Decimal point flag
        int decPoint = 0;
        // Counter of digits after decimal point
        int afterPointDigits = 0;
        
        inputExpression.clear();
        outputExpression.clear();
        
        // Place the input string into the input vector
        for (int i=0; i < (int)infixInput.length(); i++) {
            const string token(1, infixInput[i]);
            inputExpression.push_back(token);
        }

        // Replace commas with periods as decimal points in numbers
        for (int i =0; i < inputExpression.size(); i++) {
            if (inputExpression[i] == ",") {
                inputExpression[i] = ".";
            }
        }
        
        // Shunting-yard algorithm converting
        // infix input to RPN output.
        for (int i =0; i < inputExpression.size(); i++) {
            // Current expression token
            const string token = inputExpression[i];
                        
            // If current token is a digit,
            // push it onto the output queue.
            if (isDigit(token)) {
                
                if (afterPointDigits == 2) {
                    cout << "Error: the calculator does not support "
                            "more than two digits after decimal separator\n";
                    return false;
                }
                else {
                    outputExpression.push_back(token);
                    // Set the number flag indicating a number
                    // is being read from the expression
                    if (number == 0) {
                        number = 1;
                    }
                    // Increase the counter of digits
                    // located after the decimal point.
                    if (decPoint == 1) {
                        afterPointDigits++;
                    }
                    // If end of expression or end of number is reached,
                    // push whitespace to the output queue as an indicator
                    // and reset the flags.
                    if (((i+1) == inputExpression.size()) ||
                      (isWhitespace(inputExpression[i+1]) || 
                      isParenthesis(inputExpression[i+1]) ||
                       isOperator(inputExpression[i+1]))) {
                        
                        outputExpression.push_back(" ");
                        number = 0;
                        decPoint = 0;
                        afterPointDigits = 0;
                    }
                }
            }
            
            // If current token is a decimal point within a number
            else if ((token == ".") && (number == 1)) {
                
                if (decPoint == 0) {
                    decPoint = 1;
                    outputExpression.push_back(token);
                    // If end of expression is reached,
                    // or a token after decimal point is not a digit
                    // or another decimal point,
                    // the decimal point is placed incorrectly.
                    if (((i+1) == inputExpression.size()) || 
                          (!isDigit(inputExpression[i+1]) && 
                            inputExpression[i+1] != ".")) {
                        
                        cout << "Error: incorrect placement of "
                                "a decimal separator in the expression.\n";
                        return false;
                    }
                }
                else {
                    cout << "Error: the expression contains too many "
                            "decimal separators in a number.\n";
                    return false;
                }
            }
            
            // If current token is a decimal point outside a number
            // or at the beginning of a number.
            else if ((token == ".") && (number == 0)) {
                cout << "Error: incorrect placement of "
                        "a decimal separator in the expression.\n";
                return false;
            }
        
            // If current token is a sign
            // (a unary operator with right associativity),
            // it has the highest precedence.
            // It is pushed to the output queue
            // as a "p" for unary + and "m" for unary -
            // to distinguish it from operations
            // of addition and subtraction
            else if (isSign(i, token, inputExpression[i-1])) {
                if (token == "+") operStack.push("p");
                else operStack.push("m");
            }
            
            // If current token is a left-associative operator,
            // push it to the operator stack, taking into account
            // operator precedence.
            else if (isOperator(token)) {
                // current operator oper1
                const string oper1 = token;
                
                // While there is operator oper2 at the top of operator stack
                while (!operStack.empty()) {
                    // operator oper2 on top of the stack
                    string oper2 = operStack.top();

                    // Precedence of oper1 is less or equal to that of oper2
                    if (((oper2 == "p") || (oper2 == "m")) ||
                       (isOperator(oper2) && (comparePrecedence(oper1, oper2) < 0))) {
                        // Pop oper2 off the stack onto the output queue.
                        operStack.pop();
                        outputExpression.push_back(oper2);
                    }
                    else break;
                }
                // Push oper1 onto the operator stack.
                operStack.push(oper1);
            }
            
            // If current token is a left parenthesis,
            // push it onto the operator stack.
            else if (isLeftParenthesis(token)) {
                operStack.push(token);
            }
            
            // If current token is a right parenthesis,
            else if (isRightParenthesis(token)) {
                // Until left parenthesis is found at the top of the stack
                // or the end of the stack is reached.
                while (!operStack.empty() && !isLeftParenthesis(operStack.top())) {
                    // Pop elements off the operator stack
                    // and push them onto the output queue.
                    outputExpression.push_back(operStack.top());
                    operStack.pop();
                }
                // If the stack runs out without finding a left parenthesis
                // there are mismatched parentheses.
                if (operStack.empty()) {
                    cout << "Error: mismatched parentheses" << endl;
                    return false;
                }
                // Otherwise, pop left parenthesis off the operator stack,
                // but not onto the output queue.
                else {
                    operStack.pop();
                }
            }
            
            else if (isLetter(token)) {
                cout << "Error: expression contains letters,"
                        " their use is not allowed" << endl;
                return false;
            }
            
            else if (isNotValid(token)) {
                cout << "Error: expression contains invalid characters" << endl;
                return false;
            }
        }
        
        while (!operStack.empty()) {
            // If the element on top of the stack is a parenthesis
            if (isParenthesis(operStack.top())) {
                cout << "Error: mismatched parentheses" << endl;
                return false;
            }
            // Pop operators off the stack onto the output queue.
            outputExpression.push_back(operStack.top());
            operStack.pop();
        }
        return true;
    }
    
    // Evaluates the expression written in RPN using a stack.
    // Returns evaluation result rounded to two digits after decimal point.
    // Returns maximal value for a double (DBL_MAX), if unsuccessful.
    double ExpressionParser::evaluateRPN() {
        // Stack used to store operands
        stack<string> stack;
        // String used to store floating point numbers
        string number;
        // Final result
        double result = 0.0;
        
        for (int i = 0; i < (int) outputExpression.size(); i++) {
            // Intermediate result
            double interResult = 0.0;
            // Current expression token
            const string token = outputExpression[i];
            
            // If token is part of a number, 
            // store it temporarily in a string
            if (isDigit(token) || (token == ".")) {
                number.append(token);
            }
            
            // When end of number is encountered, 
            // push the number to the stack.
            else if (isWhitespace(token)) {
                stack.push(" ");
                ostringstream s;
                s << number;
                stack.push(s.str());
                number = "";
            }
            
            // If token is a sign,
            // pop the top value off the stack.
            else if ((token == "p") || (token == "m")) {                
                // Check if the operand is there
                if (!stack.empty()) {
                    // Pop the operand.
                    const string o = stack.top();
                    const double d = strtod(o.c_str(), NULL);
                    stack.pop();
                    // Whitespace is not popped off the stack,
                    // as it will separate the result from other values.
                    if (token == "m") {
                        interResult = d * -1;
                    }
                    else {
                        interResult = d;
                    }
                    // Push result onto stack
                    ostringstream s;
                    s << interResult;
                    stack.push(s.str());
                }
                else {
                    cout << "Error: insufficient operands in the expression.\n";
                    return DBL_MAX;
                }
            }
            
            // If token is an operator,
            // pop two top values off the stack.
            else if (isOperator(token)) {                
                //Check if second operand is there
                if (!stack.empty()) {
                    // Pop the second operand
                    string o2 = stack.top();
                    const double d2 = strtod(o2.c_str(), NULL);
                    stack.pop();
                    // Whitespace is popped off the stack.
                    stack.pop();
                
                    //Check if first operand is there
                    if (!stack.empty()) {
                        // pop the first operand
                        string o1 = stack.top();
                        const double d1 = strtod(o1.c_str(), NULL);
                        stack.pop();
                        // Whitespace is popped off the stack.
                        stack.pop();
                    
                        // Get the result
                        if (!(d2 == 0)) {
                            interResult = token == "+" ? d1 + d2:
                                          token == "-" ? d1 - d2:
                                          token == "*" ? d1 * d2:
                                                         d1 / d2;
                        }
                        else {
                            cout << "Error: division by zero is illegal\n";
                            return DBL_MAX;
                        }
                    }
                    else {
                        cout << "Error: insufficient operands in the expression.\n";
                        return DBL_MAX;
                    }
                    // Push whitespace to separate
                    // the result from other values
                    stack.push(" ");
                    // Push result onto stack
                    ostringstream s;
                    s << interResult;
                    stack.push(s.str());
                }
                else {
                    cout << "Error: insufficient operands in the expression.\n";
                    return DBL_MAX;
                }
            }
        }
        // Read the top value off the stack.
        result = strtod(stack.top().c_str(), NULL);
        stack.pop();
        // Whitespace is popped off the stack.
        stack.pop();
        // If there is only one value left in the stack,
        if (stack.empty()) 
            // it is the result.
            return round(result * 100) / 100;
        else {
            // Otherwise, there are too many values in user input.
            cout << "Error: excessive operands in the expression.\n";
            return DBL_MAX;
        }
    }
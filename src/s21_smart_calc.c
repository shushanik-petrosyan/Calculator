/**
 * @file s21_smartcalc.c
 * @brief This file contains an implementation of the calculator, where all
 * auxiliary functions are called to provide mathematical calculations. Namely:
 * checking the input string, splitting it into tokens, translating it into
 * Polish notation and calculations.
 */

/*!
 * \mainpage
 * \author kristinv
 * \version 1.0
 *
 * \section intro_sec Calculator_v1.0
 * This project was developed using:
 * 1. C language
 * 2. Qt Creator, Qt
 * 3. QCustomPlot
 * 4. QMake6
 * 5. Doxygen
 *
 * \section brief_sec Brief
 * This file contains an implementation of the calculator, where all auxiliary
functions are called to provide mathematical calculations. Namely:
 * checking the input string, splitting it into tokens, translating it into
Polish notation and calculations. Graph rendering is included in the
functionality of the mathematical calculator. Also included in the project is a
loan calculator that calculates the payment (annuity and differential).
 *
 * \section RPN_sec Reverse polish notation
As long as there are unprocessed lexemes in the input string, we read the next
one:

- If the lexeme is a **number**, we add it to the output string.
- If the lexeme is a **function** or an **opening bracket**, we push it onto the
stack.
- For a function argument separator (e.g., comma):
    - Transfer operators from the stack to the output queue until the lexeme at
the top of the stack becomes an opening bracket.

Operator (O1):

- While there is an operator lexeme (O2) on top of the stack with a higher
priority than O1 or, in case of equal priorities, is left-associative:
    - Transfer O2 from the stack to the output queue.
- Place O1 on the stack.

Closing bracket:

- While the lexeme at the top of the stack is not an opening bracket, transfer
operator lexemes from the stack to the output queue.
- Remove the opening bracket from the stack.
- If the lexeme at the top of the stack is a function, transfer it to the output
queue.
- If the stack is empty before encountering an opening bracket, there is an
error in the expression.

If there are no more lexemes in the input string:

- While there are operators in the stack:
    - If there is a bracket at the top of the stack, there is an error in the
expression.
    - Transfer the operator from the stack to the output queue.

 */
#include "s21_smart_calc.h"

/**
 * @brief Perform a calculation using the given input string.
 * Parses the string, converts it to reverse Polish notation, performs
 * calculation, and returns the status.
 *
 * @param src The input string to be evaluated.
 * @param result The result of the calculation.
 * @return SUCCESS if the calculation is successful, FAIL otherwise.
 */
int s21_smart_calc(char *src, long double *result, double x) {
  int status = s21_validator(src);
  *result = 0.0L;
  if (status == SUCCESS) {
    elem_node *infix_notation = NULL;
    status = s21_parse_string(src, &infix_notation, x);
    elem_node *RPN = NULL;
    s21_reverse_polish_notation(&infix_notation, &RPN);
    status = s21_calculate(&RPN, result);
    s21_free_stack(&infix_notation);
    s21_free_stack(&RPN);
  }
  return status;
}
/**
 * @file s21_calculate.c
 * @brief This file contains a function that calculates the desired value based
 * on an expression written in Polish notation. As soon as an operator is
 * encountered, the values before it are checked
 */

#include "s21_smart_calc.h"

/**
 @brief Performs binary operations (addition, subtraction, division,
 multiplication, exponentiation, modulo) based on the specified operation type.
 @param result: Result of the calculation, updated within the function.
 @param val1: First value for the binary operation.
 @param val2: Second value for the binary operation.
 @param type: Type of operation to be performed (BINARY_PLUS, BINARY_MINUS, DIV,
MUL, POW, MOD).
 @return: Status of the operation (SUCCESS if successful, FAIL if there was a
problem like division by zero).
**/
int calculate_binary(long double *result, long double val1, long double val2,
                     elem_type type) {
  int status = SUCCESS;
  *result = 0.;
  if (type == BINARY_PLUS) {
    *result = val1 + val2;
  } else if (type == BINARY_MINUS) {
    *result = val1 - val2;
  } else if (type == DIV) {
    if (val2 == 0) {
      status = FAIL;
      if (val1 > 0)
        *result = INFINITY;
      else
        *result = NAN;
    } else {
      *result = val1 / val2;
    }
  } else if (type == MUL) {
    *result = val1 * val2;
  } else if (type == POW) {
    if (val2 < 0)
      status = FAIL;
    else
      *result = pow(val1, val2);
  } else if (type == MOD) {
    if (val2 != 0)
      *result = fmod(val1, val2);
    else
      status = FAIL;
  }
  return status;
}

/**
 @brief Performs unary operations (trigonometric functions, square root, natural
logarithm, base 10 logarithm) based on the specified operation type.
 @param result: Result of the calculation, updated within the function.
 @param value: Value for the unary operation.
 @param type: Type of operation to be performed (COS, SIN, TAN, ACOS, ASIN,
ATAN, SQRT, LN, LOG).
 @return: Status of the operation (SUCCESS if successful, FAIL if there was a
problem like square root of a negative number or logarithm of a non-positive
number).
**/
int calculate_unary(long double *result, long double value, elem_type type) {
  int status = SUCCESS;
  *result = 0.;
  if (type == COS) {
    *result = cos(value);
  } else if (type == SIN) {
    *result = sin(value);
  } else if (type == TAN) {
    *result = tan(value);
  } else if (type == ACOS) {
    if (fabs((double)value) >= 1)
      status = FAIL;
    else
      *result = acos(value);
  } else if (type == ASIN) {
    if (fabs((double)value) >= 1)
      status = FAIL;
    else
      *result = asin(value);
  } else if (type == ATAN) {
    *result = atan(value);
  } else if (type == SQRT) {
    if (value < 0.)
      status = FAIL;
    else
      *result = sqrt(value);
  } else if (type == LN) {
    if (value <= 0.)
      status = FAIL;
    else
      *result = log(value);
  } else if (type == LOG) {
    if (value <= 0.)
      status = FAIL;
    else
      *result = log10(value);
  }
  return status;
}

/**
 @brief Evaluates a mathematical expression in Reverse Polish Notation (RPN) by
performing unary and binary operations.
 @param RPN: Pointer to the head of the RPN expression linked list.
 @param result: Result of the evaluation, updated within the function.
 @return: Status of the evaluation (SUCCESS if successful, FAIL if there was an
issue during evaluation).
**/
int s21_calculate(elem_node **RPN, long double *result) {
  int status = SUCCESS;
  s21_reverse_elem_node(RPN);
  double buffer_current = 0.;
  double buffer_prev = 0.;
  elem_node *stack = {0};
  while ((*RPN) != NULL && status == SUCCESS) {
    if ((*RPN)->type == NUMBER) {
      status = s21_push(&stack, (*RPN)->value, NUMBER, (*RPN)->priority);
    } else if ((*RPN)->type == X_NUMBER) {
      status = s21_push(&stack, (*RPN)->value, NUMBER, (*RPN)->priority);
    } else if (status == SUCCESS) {
      if (((*RPN)->priority == 3) && stack != NULL) {
        buffer_current = stack->value;
        status = calculate_unary(&stack->value, buffer_current, (*RPN)->type);
      } else {
        if (stack && stack->prev) {
          buffer_current = stack->value;
          buffer_prev = stack->prev->value;
          s21_pop(&stack);
          status = calculate_binary(&stack->value, buffer_prev, buffer_current,
                                    (*RPN)->type);
        } else
          status = FAIL;
      }
    } else {
      status = FAIL;
    }

    s21_pop(RPN);
  }
  *result = stack->value;
  s21_free_stack(&stack);
  s21_free_stack(RPN);
  return status;
}

/**
 * @file s21_smart_calc.h
 * @brief This file contains the declaration of all functions, the structure of
 * the stack element and the enum used for parsing
 */

#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SUCCESS 0
#define FAIL 1
#define SPACE " \n\t\v\f\r"

/**
 * @brief Enumeration representing different types of elements in a mathematical
 * expression parser. It includes numbers, variables, arithmetic operations,
 * mathematical functions, and parentheses.
 */
typedef enum {
  NUMBER,
  X_NUMBER,

  BINARY_PLUS,
  BINARY_MINUS,
  UNARY_MINUS,
  UNARY_PLUS,

  MUL,
  DIV,
  MOD,

  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,

  POW,

  OPEN_BRCKT,
  CLOSE_BRCKT,
} elem_type;

/**
 * @brief Structure representing an element of the stack.
 */
typedef struct elem {
  struct elem *prev;
  int priority;
  long double value;
  elem_type type;
} elem_node;

int s21_validator(char *src);
int check_if_mod(char **str);
int check_if_unary_func(char **str, int *status);
void valid_chars_after_START(char *current, int *is_zero, int *char_type,
                             int *bracket_count, char **copy_src, int *status);
void valid_chars_after_DIGIT_and_X(char *current, int *is_zero, int *char_type,
                                   int *bracket_count, char **copy_src,
                                   int *status, int *dot_checker,
                                   int *char_last_type);
void valid_chars_after_UNARY_PLUS_or_MINUS(char *current, int *is_zero,
                                           int *char_type, int *bracket_count,
                                           char **copy_src, int *status);
void valid_chars_after_BINARY_OPERATION(char *current, int *is_zero,
                                        int *char_type, int *bracket_count,
                                        char **copy_src, int *status);
void valid_chars_after_OPEN_BRACKET(char *current, int *is_zero, int *char_type,
                                    int *bracket_count, char **copy_src,
                                    int *status);
void valid_chars_after_CLOSE_BRACKET(char *current, char **copy_src,
                                     int *char_type, int *bracket_count,
                                     int *status);
void valid_chars_after_UNARY_OPERATION_FUNC(char *current, int *char_type,
                                            int *bracket_count, int *status);
void valid_chars_after_DOT(char *current, char **copy_src, int *char_type,
                           int *dot_checker, int *is_zero, int *bracket_count);

int s21_push(elem_node **head, long double value, elem_type type, int priority);
elem_node s21_pop(elem_node **head);
void s21_free_stack(elem_node **head);
void s21_reverse_elem_node(elem_node **head);

int s21_parse_string(char *src, elem_node **head, double x);
char *parse_function(char *src, int *status, elem_node **head);
char *parse_one_char(char *src, int *status, int flag, elem_node **head,
                     double x);
char *parse_number(char *src, int *status, elem_node **head);
int check_priority(elem_type type);

void s21_reverse_polish_notation(elem_node **head, elem_node **RPN);

int calculate_binary(long double *result, long double val1, long double val2,
                     elem_type type);
int calculate_unary(long double *result, long double value, elem_type type);
int s21_calculate(elem_node **RPN, long double *result);

int s21_smart_calc(char *src, long double *result, double x);

void s21_annuity_calculation(long double credit_amount, long double month,
                             long double interest, long double *pay_for_month,
                             long double *total_payment, long double *overpay);
void s21_diff_calculation(long double credit_amount, long double month,
                          long double interest, long double *pay_for_month_min,
                          long double *pay_for_month_max,
                          long double *total_payment, long double *overpay);

int s21_deposit_calc(double initial_deposit, int period_in_months,
                     double initial_interest, int payment_periodicity,
                     int is_capitalized, double replenishment_amount,
                     double withdraw_amount, double tax_interest,
                     double *accured_interest, double *tax_amount,
                     double *deposit_amount);
#endif  // S21_SMART_CALC_H
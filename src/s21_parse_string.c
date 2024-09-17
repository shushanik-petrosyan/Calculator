/**
 * @file s21_parse_string.c
 * @brief This file contains functions that record each string token as a
 * separate stack element, with all the auxiliary information that may be useful
 * further
 */

#include "s21_smart_calc.h"
#define NUM_SIZE 256

/**
 @brief Parses a mathematical expression string and constructs an expression
linked list based on the elements encountered.
 @param src: Source string containing the mathematical expression to be parsed.
 @param head: Pointer to the head of the expression linked list where the parsed
elements will be added.
 @return: Status of the parsing operation (SUCCESS if successful, FAIL if there
was an issue during parsing).
*/
int s21_parse_string(char(*src), elem_node **head, double x) {
  int status = SUCCESS;
  char prev_char = 0;
  while (((*src)) != '\0' && status == SUCCESS) {
    int flag = 0;
    if ((prev_char == 0 || prev_char == '(') &&
        ((*src) == '-' || (*src) == '+')) {
      flag = 1;
    }
    prev_char = (*src);
    if (strchr("x*/^-+()", (*src)) != NULL)
      src = parse_one_char(src, &status, flag, head, x);
    else if (islower((int)(*src)))
      src = parse_function(src, &status, head);
    else if (isdigit((int)(*src)))
      src = parse_number(src, &status, head);
    else
      src++;
  }
  return status;
}

/**
 @brief Determines the priority of a given element type used in mathematical
expressions.
 @param type: Type of the element to check priority for.
 @return: Priority level of the element type (-1 if not found or an invalid
type).
*/
int check_priority(elem_type type) {
  int priority = -1;
  if (type == NUMBER || type == X_NUMBER) {
    priority = 0;
  } else if (type == BINARY_PLUS || type == BINARY_MINUS ||
             type == UNARY_MINUS || type == UNARY_PLUS) {
    priority = 1;
  } else if (type == MUL || type == DIV || type == MOD) {
    priority = 2;
  } else if (type == COS || type == SIN || type == TAN || type == ACOS ||
             type == ASIN || type == ATAN || type == SQRT || type == LN ||
             type == LOG) {
    priority = 3;
  } else if (type == POW) {
    priority = 4;
  } else if (type == OPEN_BRCKT || type == CLOSE_BRCKT) {
    priority = 5;
  }
  return priority;
}

/**
 @brief Parses a given function name from the source string and pushes the
corresponding operation into the expression linked list.
 @param src: Source string containing the mathematical expression.
 @param status: Status of s21_push (if there is enough memory -> success).
 @param head: Pointer to the head of the expression linked list where the
function name will be pushed.
 @return: Updated source string pointer after parsing the function name.
*/
char *parse_function(char *src, int *status, elem_node **head) {
  if (strncmp(src, "cos", strlen("cos")) == 0) {
    *status = s21_push(head, 0.0, COS, check_priority(COS));
    src += strlen("cos");
  } else if (strncmp(src, "sin", strlen("sin")) == 0) {
    *status = s21_push(head, 0.0, SIN, check_priority(SIN));
    src += strlen("sin");
  } else if (strncmp(src, "tan", strlen("tan")) == 0) {
    *status = s21_push(head, 0.0, TAN, check_priority(TAN));
    src += strlen("tan");
  } else if (strncmp(src, "log", strlen("log")) == 0) {
    *status = s21_push(head, 0.0, LOG, check_priority(LOG));
    src += strlen("log");
  } else if (strncmp(src, "ln", strlen("ln")) == 0) {
    *status = s21_push(head, 0.0, LN, check_priority(LN));
    src += strlen("ln");
  } else if (strncmp(src, "sqrt", strlen("sqrt")) == 0) {
    *status = s21_push(head, 0.0, SQRT, check_priority(SQRT));
    src += strlen("sqrt");
  } else if (strncmp(src, "acos", strlen("acos")) == 0) {
    *status = s21_push(head, 0.0, ACOS, check_priority(ACOS));
    src += strlen("acos");
  } else if (strncmp(src, "atan", strlen("atan")) == 0) {
    *status = s21_push(head, 0.0, ATAN, check_priority(ATAN));
    src += strlen("atan");
  } else if (strncmp(src, "asin", strlen("asin")) == 0) {
    *status = s21_push(head, 0.0, ASIN, check_priority(ASIN));
    src += strlen("asin");
  } else if (strncmp(src, "mod", strlen("mod")) == 0) {
    *status = s21_push(head, 0.0, MOD, check_priority(MOD));
    src += strlen("mod");
  }
  return src;
}

/**
 @brief Parses a single character operation from the source string and pushes it
into the expression linked list.
 @param src: Source string containing the character to be parsed.
 @param status: Status of s21_push (if there is enough memory -> success).
 @param flag: Flag indicating if the current character is part of a number.
 @param head: Pointer to the head of the expression linked list where the
operation will be pushed.
 @return: Updated source string pointer after parsing the character.
*/
char *parse_one_char(char *src, int *status, int flag, elem_node **head,
                     double x) {
  if (*src == 'x') {
    *status = s21_push(head, (long double)x, NUMBER, check_priority(NUMBER));
    src++;
  } else if (*src == '*') {
    *status = s21_push(head, 0.0, MUL, check_priority(MUL));
    src++;
  } else if (*src == '/') {
    *status = s21_push(head, 0.0, DIV, check_priority(DIV));
    src++;
  } else if (*src == '^') {
    *status = s21_push(head, 0.0, POW, check_priority(POW));
    src++;
  } else if (*src == '-') {
    if (flag) {
      *status = s21_push(head, 0.0, NUMBER, check_priority(NUMBER));
    }
    *status = s21_push(head, 0.0, BINARY_MINUS, check_priority(BINARY_MINUS));
    src++;
  } else if (*src == '+' && !flag) {
    *status = s21_push(head, 0.0, BINARY_PLUS, check_priority(BINARY_PLUS));
    src++;
  } else if (*src == ')') {
    *status = s21_push(head, 0.0, CLOSE_BRCKT, check_priority(CLOSE_BRCKT));
    src++;
  } else if (*src == '(') {
    *status = s21_push(head, 0.0, OPEN_BRCKT, check_priority(OPEN_BRCKT));
    src++;
  }
  return src;
}

/**
 @brief Parses a number from the source string and pushes it into the expression
linked list.
 @param src: Source string containing the number to be parsed.
 @param status:Status of s21_push (if there is enough memory -> success).
 @param head: Pointer to the head of the expression linked list where the number
will be pushed.
 @return: Updated source string pointer after parsing the number.
*/
char *parse_number(char *src, int *status, elem_node **head) {
  char number[NUM_SIZE];
  int i = 0;
  while ((isdigit((int)*src) || *src == '.' || strchr(SPACE, *src) != NULL) &&
         *src != '\0') {
    if (strchr(SPACE, *src) == NULL)
      number[i++] = *src++;
    else
      src++;
  }
  memset(number + i, '\0', sizeof(number) - i);
  *status = s21_push(head, atof(number), NUMBER, check_priority(NUMBER));
  return src;
}

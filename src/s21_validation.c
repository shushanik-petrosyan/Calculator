/**
 * @file s21_vaidation.c
 * @brief This file contains a function that checks the correctness of the
 * entered string from a mathematical point of view, and other auxiliary
 * functions.
 */

#include "s21_smart_calc.h"

enum info {
  START,
  DIGIT,
  X,
  UNARY_OPERATION,
  BINARY_OPERATION,
  DOT,
  OPEN_BRACKET,
  CLOSE_BRACKET,
  UNARY_OPERATION_FUNC,
} symbol_info;

const char *numbers = "0123456789\0";
const char *unary_operation = "+-\0";
const char *binary_operation = "+-*/^\0";

/**
 * @brief Validate a string using a specific set of rules for a mathematical
 * expression. Checks if the input string follows the syntax rules specified by
 * the function calls.
 *
 * @param src The input string to be validated.
 * @return SUCCESS if the string follows the syntax rules, FAIL otherwise.
 */
int s21_validator(char *src) {
  int status = SUCCESS, char_type = 0, char_last_type = 0, is_zero = 0,
      bracket_count = 0, dot_checker = 0;
  char *copy_src = src;
  while (*copy_src != '\0' && status == SUCCESS) {
    char current = *copy_src;
    if (char_last_type == START) {
      valid_chars_after_START(&current, &is_zero, &char_type, &bracket_count,
                              &copy_src, &status);
    } else if (char_last_type == DIGIT || char_last_type == X) {
      valid_chars_after_DIGIT_and_X(&current, &is_zero, &char_type,
                                    &bracket_count, &copy_src, &status,
                                    &dot_checker, &char_last_type);
    } else if (char_last_type == UNARY_OPERATION) {
      valid_chars_after_UNARY_PLUS_or_MINUS(&current, &is_zero, &char_type,
                                            &bracket_count, &copy_src, &status);
    } else if (char_last_type == BINARY_OPERATION) {
      valid_chars_after_BINARY_OPERATION(&current, &is_zero, &char_type,
                                         &bracket_count, &copy_src, &status);
    } else if (char_last_type == OPEN_BRACKET) {
      valid_chars_after_OPEN_BRACKET(&current, &is_zero, &char_type,
                                     &bracket_count, &copy_src, &status);
    } else if (char_last_type == CLOSE_BRACKET) {
      valid_chars_after_CLOSE_BRACKET(&current, &copy_src, &char_type,
                                      &bracket_count, &status);
    } else if (char_last_type == UNARY_OPERATION_FUNC) {
      valid_chars_after_UNARY_OPERATION_FUNC(&current, &char_type,
                                             &bracket_count, &status);
    } else if (char_last_type == DOT) {
      valid_chars_after_DOT(&current, &copy_src, &char_type, &dot_checker,
                            &is_zero, &bracket_count);
    }
    char_last_type = char_type;
    copy_src++;
  }
  if (status == SUCCESS) {
    if (bracket_count != 0) {
      status = FAIL;
    } else if (char_last_type != DIGIT && char_last_type != X &&
               char_last_type != CLOSE_BRACKET && char_last_type != DOT)
      status = FAIL;
  }
  return status;
}

/**
 * @brief Check if the input string ends with the word "mod".
 * @param str The input string to check.
 *
 * @return Returns 1 if the input string ends with "mod", 0 otherwise.
 */
int check_if_mod(char **str) {
  int status = 0;
  const char *target_word = "mod";
  if (strncmp(*str, target_word, strlen(target_word)) == 0) {
    *str += strlen(target_word) - 1;
    status = 1;
  }
  return status;
}

/**
 * @brief Check if the input string corresponds to a unary function and update
 * the status.
 *
 * @param str The input string to check.
 * @param status The current status to be updated upon checking.
 *
 * @return Returns 1 if the input string matches a unary function, 0 otherwise.
 */
int check_if_unary_func(char **str, int *status) {
  const char *target_word[] = {"cos",  "sin",  "tan", "acos", "asin",
                               "atan", "sqrt", "ln",  "log"};
  int status_of_check = 0;
  int is_not_space = 0;
  int num_words = sizeof(target_word) / sizeof(target_word[0]);
  for (int i = 0; i < num_words; i++) {
    if (strncmp(*str, target_word[i], strlen(target_word[i])) == 0) {
      status_of_check = 1;
      *str += strlen(target_word[i]) - 1;
    }
  }
  is_not_space = strchr(SPACE, **str) == NULL;
  if (status_of_check == 0 && is_not_space) *status = FAIL;
  return status_of_check;
}

/**
 * @brief Validate the characters that can appear after the start character.
 *
 * @param current The current character being analyzed.
 * @param is_zero Flag indicating if the current character is '0'.
 * @param char_type The type of character encountered.
 * @param bracket_count The current count of brackets.
 * @param copy_src The source character.
 * @param status The current status to be updated if needed.
 */
void valid_chars_after_START(char *current, int *is_zero, int *char_type,
                             int *bracket_count, char **copy_src, int *status) {
  if (strchr(numbers, *current)) {
    *char_type = DIGIT;
    if (*current == '0') *is_zero = 1;
  } else if (strchr(unary_operation, *current)) {
    *char_type = UNARY_OPERATION;
  } else if (*current == 'x') {
    *char_type = X;
  } else if (*current == '(') {
    *char_type = OPEN_BRACKET;
    ++*bracket_count;
  } else {
    if (check_if_unary_func(copy_src, status))
      *char_type = UNARY_OPERATION_FUNC;
  }
}

/**
 * @brief Validate the characters that can appear after a digit or 'x'.
 *After the digit, you can perform a binary operation that closes the bracket,
 digit, period. After x, you can: only the binary operation that closes the
 bracket

 * @param current The current character being analyzed.
 * @param is_zero Flag indicating if the current character is '0'.
 * @param char_type The type of character encountered.
 * @param bracket_count The current count of brackets.
 * @param copy_src The source character.
 * @param status The current status to be updated if needed.
 * @param dot_checker Checker for the presence of a decimal point.
 * @param char_last_type The type of the last character encountered.
 */
void valid_chars_after_DIGIT_and_X(char *current, int *is_zero, int *char_type,
                                   int *bracket_count, char **copy_src,
                                   int *status, int *dot_checker,
                                   int *char_last_type) {
  if (strchr(binary_operation, *current) || check_if_mod(copy_src)) {
    *char_type = BINARY_OPERATION;
    *is_zero = 0;
    *dot_checker = 0;
  } else if (*current == ')') {
    *char_type = CLOSE_BRACKET;
    *dot_checker = 0;
    (*bracket_count)--;
  } else if (*char_last_type == DIGIT) {
    if (strchr(numbers, *current)) {
      *char_type = DIGIT;
      if (*is_zero == 1) {
        *status = FAIL;
      }
    } else if (*current == '.' && *dot_checker == 0) {
      *char_type = DOT;
      *dot_checker = 1;
    } else {
      if (strchr(SPACE, *current) == NULL) *status = FAIL;
    }

  } else {
    if (strchr(SPACE, *current) == NULL) *status = FAIL;
  }
}

/**
 * @brief Validate the characters that can appear after a unary plus or minus.
 *  Valid characters are digit, x, (, unary function.
 * @param current The current character being analyzed.
 * @param is_zero Flag indicating if the current character is '0'.
 * @param char_type The type of character encountered.
 * @param bracket_count The current count of brackets.
 * @param copy_src The source character.
 * @param status The current status to be updated if needed.
 */
void valid_chars_after_UNARY_PLUS_or_MINUS(char *current, int *is_zero,
                                           int *char_type, int *bracket_count,
                                           char **copy_src, int *status) {
  if (strchr(numbers, *current)) {
    *char_type = DIGIT;
    if (*current == '0') *is_zero = 1;
  } else if (*current == 'x')
    *char_type = X;
  else if (*current == '(') {
    *char_type = OPEN_BRACKET;
    (*bracket_count)++;
  } else {
    if (check_if_unary_func(copy_src, status))
      *char_type = UNARY_OPERATION_FUNC;
  }
}

/**
 * @brief Validate the characters that can appear after a binary operation.
 *  Valid characters are digit, x, (, unary function
 * @param current The current character being analyzed.
 * @param is_zero Flag indicating if the current character is '0'.
 * @param char_type The type of character encountered.
 * @param bracket_count The current count of brackets.
 * @param copy_src The source character.
 * @param status The current status to be updated if needed.
 */
void valid_chars_after_BINARY_OPERATION(char *current, int *is_zero,
                                        int *char_type, int *bracket_count,
                                        char **copy_src, int *status) {
  if (strchr(numbers, *current)) {
    *char_type = DIGIT;
    if (*current == '0') *is_zero = 1;
  } else if (*current == 'x')
    *char_type = X;
  else if (*current == '(') {
    *char_type = OPEN_BRACKET;
    (*bracket_count)++;
  } else {
    if (check_if_unary_func(copy_src, status))
      *char_type = UNARY_OPERATION_FUNC;
  }
}

/**
 * @brief Validate the characters that can appear after an open bracket.
 * Valid characters are digit, x, (, unary function
 * @param current The current character being analyzed.
 * @param is_zero Flag indicating if the current character is '0'.
 * @param char_type The type of character encountered.
 * @param bracket_count The current count of  brackets.
 * @param copy_src The source character.
 * @param status The current status to be updated if needed.
 */
void valid_chars_after_OPEN_BRACKET(char *current, int *is_zero, int *char_type,
                                    int *bracket_count, char **copy_src,
                                    int *status) {
  if (strchr(numbers, *current)) {
    *char_type = DIGIT;
    if (*current == '0') *is_zero = 1;
  } else if (*current == 'x')
    *char_type = X;
  else if (strchr(unary_operation, *current))
    *char_type = UNARY_OPERATION;
  else if (*current == '(') {
    *char_type = OPEN_BRACKET;
    (*bracket_count)++;
  } else {
    if (check_if_unary_func(copy_src, status))
      *char_type = UNARY_OPERATION_FUNC;
  }
}

/**
 * @brief Validate the characters that can appear after a close bracket.
 * Valid characters are binary operations (including mod) and close bracket
 * @param current The current character being analyzed.
 * @param copy_src The source character.
 * @param char_type The type of character encountered.
 * @param bracket_count The current count of brackets.
 * @param status The current status to be updated if needed.
 */
void valid_chars_after_CLOSE_BRACKET(char *current, char **copy_src,
                                     int *char_type, int *bracket_count,
                                     int *status) {
  if (strchr(binary_operation, *current) || check_if_mod(copy_src))
    *char_type = BINARY_OPERATION;
  else if (*current == ')') {
    *char_type = CLOSE_BRACKET;
    (*bracket_count)--;
  } else {
    if (strchr(SPACE, *current) == NULL) *status = FAIL;
  }
}

/**
 * @brief Validate the characters that can appear after a unary operation
 * function. Valid character is open bracketю
 * @param current The current character being analyzed.
 * @param char_type The type of character encountered.
 * @param bracket_count The current count of brackets.
 * @param status The current status to be updated if needed.
 */
void valid_chars_after_UNARY_OPERATION_FUNC(char *current, int *char_type,
                                            int *bracket_count, int *status) {
  if (*current == '(') {
    *char_type = OPEN_BRACKET;
    (*bracket_count)++;
  } else {
    if (strchr(SPACE, *current) == NULL) *status = FAIL;
  }
}

/**
 * @brief Validate the characters that can appear after a dot in a mathematical
 * expression. Valid characters are binary operation, digit and close bracketю
 * @param current The current character being analyzed.
 * @param copy_src The character preceding the dot.
 * @param char_type The type of character encountered.
 * @param dot_checker Flag to check if a dot is present.
 * @param is_zero Flag to check if the digit is zero.
 * @param bracket_count The current count of brackets.
 */
void valid_chars_after_DOT(char *current, char **copy_src, int *char_type,
                           int *dot_checker, int *is_zero, int *bracket_count) {
  if (strchr(binary_operation, *current) || check_if_mod(copy_src)) {
    *char_type = BINARY_OPERATION;
    *dot_checker = 0;
    *is_zero = 0;
  } else if (*current == ')') {
    *dot_checker = 0;
    *char_type = CLOSE_BRACKET;
    (*bracket_count)--;
  } else if (strchr(numbers, *current)) {
    *char_type = DIGIT;
    *is_zero = 0;
  }
}
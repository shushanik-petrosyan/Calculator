/**
 * @file s21_RPN.c
 * @brief This file contains function, that make reverse polish notatiom from
 * infix expression
 */

#include "s21_smart_calc.h"

/**
 @brief Converts an infix expression stored as a linked list into Reverse Polish
Notation (RPN) format.
In reverse Polish notation, the operators follow their operands. For example, to
add 3 and 4 together, the expression is 3 4 + rather than 3 + 4. The
conventional notation expression 3 − 4 + 5 becomes 3 4 − 5 + in reverse Polish
notation: 4 is first subtracted from 3, then 5 is added to it.

The concept of a stack, a last-in/first-out construct, is integral to the
left-to-right evaluation of RPN. In the example 3 4 −, first the 3 is put onto
the stack, then the 4; the 4 is now on top and the 3 below it. The subtraction
operator removes the top two items from the stack, performs 3 − 4, and puts the
result of −1 onto the stack.
 @param head: Pointer to the head of the infix expression linked list.
 @param RPN: Pointer to the head of the RPN expression linked list produced from
the infix expression.
*/
void s21_reverse_polish_notation(elem_node **head, elem_node **RPN) {
  s21_reverse_elem_node(head);
  elem_node *operators = {0};
  while (*head != NULL) {
    if ((*head)->priority == 0) {
      s21_push(RPN, (*head)->value, (*head)->type, (*head)->priority);
    } else {
      while (operators != NULL && ((operators->priority >= (*head)->priority &&
                                    operators->type != OPEN_BRCKT) ||
                                   ((*head)->type == CLOSE_BRCKT))

      ) {
        if (operators->type != OPEN_BRCKT)
          s21_push(RPN, operators->value, operators->type, operators->priority);
        else {
          s21_pop(&operators);
          break;
        }
        s21_pop(&operators);
      }
      if ((*head)->type != CLOSE_BRCKT)
        s21_push(&operators, (*head)->value, (*head)->type, (*head)->priority);
    }
    s21_pop(head);
  }

  while (operators != NULL) {
    s21_push(RPN, operators->value, operators->type, operators->priority);
    s21_pop(&operators);
  }
  s21_free_stack(&operators);
}
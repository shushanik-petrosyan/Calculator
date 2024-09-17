/**
 * @file s21_stack.c
 * @brief This file contains the functions necessary to work with the stack data
 * structure.
 */

#include "s21_smart_calc.h"

/**
 @brief Pushes a new element onto the top of the stack.
Allocate memory for the new element. Set value, type, and priority for the new
element. Set the prev pointer of the new element to point to the current top
element of the stack. Move the head of the stack to the new element, making it
the new top of the stack
 @param head: Pointer to the head of the stack.
 @param value: Value to be stored in the new element.
 @param type: Type of the element (operand or operator).
 @param priority: Priority level of the element in the expression.
 @return: Status of the push operation (SUCCESS if successful, FAIL if
allocation failed).
*/
int s21_push(elem_node **head, long double value, elem_type type,
             int priority) {
  int status = SUCCESS;
  elem_node *tmp = (elem_node *)calloc(1, sizeof(elem_node));
  if (tmp != NULL) {
    tmp->value = value;
    tmp->type = type;
    tmp->priority = priority;
    tmp->prev = (*head);

    (*head) = tmp;
  } else {
    status = FAIL;
  }

  return status;
}

/**
 @brief Removes the top element from the stack.
 @param head: Pointer to the head of the stack.
 @return: Element removed from the stack, or an empty element if the stack is
empty.
*/
elem_node s21_pop(elem_node **head) {
  elem_node *ptr_to_free = NULL;
  elem_node check_value = {0};
  if (*head != NULL) {
    check_value = **head;
    ptr_to_free = *head;
    (*head) = (*head)->prev;
    free(ptr_to_free);
    ptr_to_free = NULL;
  }
  return check_value;
}

/**
 @brief Frees the memory allocated for the entire stack by deallocating each
element.
 @param head: Pointer to the head of the stack.
*/
void s21_free_stack(elem_node **head) {
  elem_node *ptr_to_free = NULL;
  while (*head != NULL) {
    ptr_to_free = *head;
    (*head) = (*head)->prev;
    free(ptr_to_free);
  }
}

/**
  @brief Reverses the order of elements in the linked list stack.
  @param head: Pointer to the head of the stack (linked list).
*/
void s21_reverse_elem_node(elem_node **head) {
  if (*head != NULL) {
    elem_node *prev = NULL;
    elem_node *next = (*head)->prev;
    while (next != NULL) {
      (*head)->prev = prev;
      prev = *head;
      *head = next;
      next = (*head)->prev;
    }
    (*head)->prev = prev;
  }
}

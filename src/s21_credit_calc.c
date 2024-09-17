/**
 * @file s21_credit_calc.c
 * @brief This file contains functions that calculate credit-related values.
 * Input: total loan amount, term, interest rate, type (annuity,
 * differentiated); Output: monthly payment, loan overpayment, total payment.
 */

#include "s21_smart_calc.h"

/**
 * @brief Function to calculate the payment details for a loan with annuities
 *
 * @param credit_amount The total amount of credit
 * @param month The number of months for the loan
 * @param interest The interest rate per year
 * @param pay_for_month The payment amount for each month
 * @param total_payment The total payment for the loan
 * @param overpay The amount overpaid for the loan
 */
void s21_annuity_calculation(long double credit_amount, long double month,
                             long double interest, long double *pay_for_month,
                             long double *total_payment, long double *overpay) {
  long double interest_for_month = interest / 100.0 / 12.0;
  *pay_for_month = credit_amount *
                   (interest_for_month * powl(1 + interest_for_month, month)) /
                   (powl(1 + interest_for_month, month) - 1);
  *total_payment = month * (roundl(*pay_for_month * 100.0) / 100.0);
  *overpay = *total_payment - credit_amount;
}

/**
 * @brief Function to calculate the payment details for a loan
 *
 * @param credit_amount The total amount of credit
 * @param month The number of months for the loan
 * @param interest The interest rate per year
 * @param pay_for_month_min The minimum payment amount for a month
 * @param pay_for_month_max The maximum payment amount for a month
 * @param total_payment The total payment for the loan
 * @param overpay The amount overpaid for the loan
 */
void s21_diff_calculation(long double credit_amount, long double month,
                          long double interest, long double *pay_for_month_min,
                          long double *pay_for_month_max,
                          long double *total_payment, long double *overpay) {
  interest = interest / 100.0 / 12.0;
  long double credit_amount_const = credit_amount / month;
  for (int i = 0; credit_amount > 0; i++) {
    *overpay += credit_amount * interest;
    if (i == 0)
      *pay_for_month_max = credit_amount * interest + credit_amount_const;
    else if (i == month - 1)
      *pay_for_month_min = credit_amount * interest + credit_amount_const;
    credit_amount -= credit_amount_const;
  }
  *total_payment = credit_amount_const * month + *overpay;
}

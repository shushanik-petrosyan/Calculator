/**
 * @file s21_deposit_calc.c
 * @brief This file contains a function that calculates deposit accruals. This
 * file is an implementation of a deposit calculator
 *
 * Input: deposit amount, placement period, interest rate, tax rate, frequency
 * of payments, capitalization of interest, list of deposits, list of partial
 * withdrawals Output: accrued interest, tax amount, deposit amount by the end
 * of the term
 */

#include "s21_smart_calc.h"
#define ONE_PERCENT 0.01
#define MONTHS_IN_YEAR 12

/**
 * @brief Function for calculating a deposit with various parameters.
 *
 * The function s21_deposit_calc calculates the deposit based on the input
 * parameters: initial deposit, period in months, initial interest rate, payment
 * periodicity, capitalization flag, replenishment amount, withdrawal amount,
 * tax interest rate, and returns accrued interest, tax amount, and total
 * deposit amount.
 *
 * @param initial_deposit Initial deposit amount.
 * @param period_in_months Period duration in months.
 * @param initial_interest Initial interest rate.
 * @param payment_periodicity Payment periodicity 1 - once a month, 12 - once a
 * year.
 * @param is_capitalized Flag indicating if the deposit is capitalized.
 * @param replenishment_amount Amount of additional deposits.
 * @param withdraw_amount Amount of withdrawals.
 * @param tax_interest Tax interest rate.
 * @param accured_interest Pointer to store the accrued interest.
 * @param tax_amount Pointer to store the tax amount.
 * @param deposit_amount Pointer to store the total deposit amount.
 * @return Success status if the calculation is successful, or Fail status if
 * period_in_months is less than payment_periodicity.
 */
int s21_deposit_calc(double initial_deposit, int period_in_months,
                     double initial_interest, int payment_periodicity,
                     int is_capitalized, double replenishment_amount,
                     double withdraw_amount, double tax_interest,
                     double* accured_interest, double* tax_amount,
                     double* deposit_amount) {
  int status = SUCCESS;
  *tax_amount = 0, *deposit_amount = 0, *accured_interest = 0;

  double interest = initial_interest * ONE_PERCENT,
         copy_initial_deposit = initial_deposit;

  if (period_in_months >= payment_periodicity) {
    for (int month = 1; month <= period_in_months; month++) {
      double accured_interest_in_month = 0;
      if (payment_periodicity == 1) {
        accured_interest_in_month =
            copy_initial_deposit * interest / MONTHS_IN_YEAR;
      } else if (payment_periodicity == MONTHS_IN_YEAR &&
                 month % MONTHS_IN_YEAR == 0) {
        accured_interest_in_month = copy_initial_deposit * interest;
      }

      if (month < period_in_months) {
        copy_initial_deposit =
            copy_initial_deposit + replenishment_amount - withdraw_amount;
      }
      if (is_capitalized) {
        copy_initial_deposit += accured_interest_in_month;
      }
      *accured_interest += accured_interest_in_month;
    }
    *tax_amount = (*accured_interest) * tax_interest * ONE_PERCENT;
    *deposit_amount =
        initial_deposit + (*accured_interest) - (*tax_amount) +
        ((replenishment_amount - withdraw_amount) * period_in_months);
  } else {
    status = FAIL;
  }
  return status;
}

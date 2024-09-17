#include <check.h>

#include "s21_smart_calc.h"

#define PREC 1e-2
#define PREC_7 1e-7

START_TEST(test_two_operators) {
  char *invalid_input = "5 +* 4";
  int result = s21_validator(invalid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(test_valid_input) {
  char *valid_input = "10 / 5 + 2 * 3";
  long double result = 0;
  long double expected_result = 8;
  int status = s21_smart_calc(valid_input, &result, 0);
  ck_assert_double_eq_tol(expected_result, result, PREC_7);
  ck_assert_int_eq(status, SUCCESS);
}
END_TEST

START_TEST(test_two_dots) {
  char *valid_input = "10.433.2 / 5 + 2 * 3";
  int result = s21_validator(valid_input);
  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(test_zero) {
  char *valid_input = "00010.433 / 5 + 2 * 3";
  int result = s21_validator(valid_input);
  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(test_zero_middle) {
  char *valid_input = "10.433 / 5 + 0002 * 3";
  int result = s21_validator(valid_input);
  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(just_symbols) {
  char *valid_input = "*&^";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(just_x) {
  char *valid_input = "x";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(invalid_brackets) {
  char *valid_input = "(5 + 3";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(invalid_brackets_2) {
  char *valid_input = "6 * (2 + 4))";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(invalid_end) {
  char *valid_input = "3 +";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(invalid_end_2) {
  char *valid_input = "6 * 3 /";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(invalid_dot) {
  char *valid_input = "1,000 + 4";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(invalid_input_symbols) {
  char *valid_input = "5 + $ 3";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(test_spaces) {
  char val[] = "10.433     / 5       + 2 *          3 + x";
  long double result = 0.0L;
  long double expected_result = 9.0866L;
  int status = s21_smart_calc(val, &result, 1);
  ck_assert_ldouble_eq_tol(expected_result, result, PREC_7);
  ck_assert_int_eq(status, SUCCESS);
}
END_TEST

START_TEST(test_spaces_2) {
  char valid_input[] =
      "10.       433             / 5                             + 2 ";
  long double result = 0.0L;
  long double expected_result = 4.0866L;
  int status = s21_smart_calc(valid_input, &result, 0);
  ck_assert_ldouble_eq_tol(expected_result, result, PREC_7);
  ck_assert_int_eq(status, SUCCESS);
}
END_TEST

START_TEST(mod) {
  char *valid_input = "10 mod 2";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(mod_invalid) {
  char *valid_input = "10 mod(2)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(sqrt_invalid) {
  char *valid_input = "10 + sqrl(2)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(sqrt_1) {
  char *valid_input = "10 + sqrt(2)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(unary_invalid) {
  char *valid_input = "-10 + sqrt(2)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(unary_valid) {
  char *valid_input = "(-10) + sqrt(2)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(binary_after_dot) {
  char *valid_input = "(-10) + 2. - 4";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(bracket_after_dot) {
  char *valid_input = "((-10) + 2. )- 4";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(log_1) {
  char *valid_input = "3/log(4)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(div_x) {
  char *valid_input = "3/x";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(unary_x_bracket) {
  char *valid_input = "-x-(5+1)+(-5)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(unary_x_bracket_2) {
  char *valid_input = "-(5+1)+(-5)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(zero_bracket) {
  char *valid_input = "-(05+1)+(-5)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(open_bracket_cases) {
  char *valid_input = "-0 + (cos(x)) + (x-1)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(start_unary) {
  char *valid_input = "cos(x)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(invalid_digit) {
  char *valid_input = "45 + 54x";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(unary_min_unary_func) {
  char *valid_input = "-cos(x)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(open_bracket_invalid_1) {
  char *valid_input = "45 + 44 + (%4)";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(close_bracket_invalid_1) {
  char *valid_input = "45 + 44 + (4)% + 7";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(unary_trash) {
  char *valid_input = "-%5 + 6";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(x_trash) {
  char *valid_input = "-5 + 6 / x% * 4";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

START_TEST(unary_func_trash) {
  char *valid_input = "45/4 + cos2";
  int result = s21_validator(valid_input);

  ck_assert_int_eq(result, FAIL);
}
END_TEST

Suite *s21_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("S21 Validator");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_two_operators);
  tcase_add_test(tc_core, test_valid_input);
  tcase_add_test(tc_core, test_two_dots);
  tcase_add_test(tc_core, test_zero);
  tcase_add_test(tc_core, test_zero_middle);
  tcase_add_test(tc_core, just_symbols);
  tcase_add_test(tc_core, just_x);
  tcase_add_test(tc_core, invalid_brackets);
  tcase_add_test(tc_core, invalid_brackets_2);
  tcase_add_test(tc_core, invalid_end);
  tcase_add_test(tc_core, invalid_end_2);
  tcase_add_test(tc_core, invalid_dot);
  tcase_add_test(tc_core, invalid_input_symbols);
  tcase_add_test(tc_core, test_spaces);
  tcase_add_test(tc_core, test_spaces_2);
  tcase_add_test(tc_core, mod);
  tcase_add_test(tc_core, mod_invalid);
  tcase_add_test(tc_core, sqrt_1);
  tcase_add_test(tc_core, sqrt_invalid);
  tcase_add_test(tc_core, unary_invalid);
  tcase_add_test(tc_core, unary_valid);
  tcase_add_test(tc_core, binary_after_dot);
  tcase_add_test(tc_core, bracket_after_dot);
  tcase_add_test(tc_core, log_1);
  tcase_add_test(tc_core, div_x);
  tcase_add_test(tc_core, unary_x_bracket);

  tcase_add_test(tc_core, unary_x_bracket_2);
  tcase_add_test(tc_core, zero_bracket);
  tcase_add_test(tc_core, open_bracket_cases);
  tcase_add_test(tc_core, start_unary);
  tcase_add_test(tc_core, invalid_digit);
  tcase_add_test(tc_core, unary_min_unary_func);
  tcase_add_test(tc_core, open_bracket_invalid_1);
  tcase_add_test(tc_core, close_bracket_invalid_1);
  tcase_add_test(tc_core, unary_trash);
  tcase_add_test(tc_core, unary_func_trash);
  tcase_add_test(tc_core, x_trash);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_1) {
  char *input = "0+0";
  long double result = 0.0L;
  long double expected_result = 0.0L;
  s21_smart_calc(input, &result, 0);
  ck_assert_double_eq_tol(expected_result, result, PREC_7);
}
END_TEST

START_TEST(test_2) {
  char *input =
      "-1 + cos(1) + sin(1) * log(10) - ln(100) - (sqrt(77.8) mod 2) - "
      "tan(54)/3 + atan(0.4) - asin(0.3) * (2^4) + acos(3) ";
  long double result = 0.0L;
  long double expected_result = 0;
  s21_smart_calc(input, &result, 0);
  ck_assert_double_eq_tol(expected_result, result, PREC_7);
}
END_TEST

START_TEST(test_3) {
  char input[] = "0/0";
  long double result = 0.0L;
  s21_smart_calc(input, &result, 0);
  result = isnan(result);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_4) {
  char input[] = "1/0";
  long double result = 0.0L;
  s21_smart_calc(input, &result, 0);
  ck_assert_ldouble_infinite(result);
}
END_TEST

START_TEST(test_5) {
  char *input = "0^(-5)";
  long double result = 0.0L;
  int status = s21_smart_calc(input, &result, 0);
  ck_assert_int_eq(status, FAIL);
}
END_TEST

START_TEST(test_6) {
  char *input = "5 mod 0";
  long double result = 0.0L;
  int status = s21_smart_calc(input, &result, 0);
  ck_assert_int_eq(status, FAIL);
}
END_TEST

START_TEST(test_7) {
  char *input = "acos(0.5) + asin(1.5)";
  long double result = 0.0L;
  int status = s21_smart_calc(input, &result, 0);
  ck_assert_int_eq(status, FAIL);
}
END_TEST

START_TEST(test_8) {
  char *input = "sqrt(-1)";
  long double result = 0.0L;
  int status = s21_smart_calc(input, &result, 0);
  ck_assert_int_eq(status, FAIL);
}
END_TEST

START_TEST(test_9) {
  char *input = "log(-1)";
  long double result = 0.0L;
  int status = s21_smart_calc(input, &result, 0);
  ck_assert_int_eq(status, FAIL);
}
END_TEST

START_TEST(test_10) {
  char *input = "ln(-1)";
  long double result = 0.0L;
  int status = s21_smart_calc(input, &result, 0);
  ck_assert_int_eq(status, FAIL);
}
END_TEST

START_TEST(test_11) {
  char *input = "5 + ln(-1) + 6";
  long double result = 0.0L;
  int status = s21_smart_calc(input, &result, 0);
  ck_assert_int_eq(status, FAIL);
}
END_TEST

START_TEST(test_12) {
  long double pay_for_month_min = 0;
  long double pay_for_month_max = 0;
  long double total_payment = 0;
  long double overpay = 0;

  s21_diff_calculation(3520000, 7, 15, &pay_for_month_min, &pay_for_month_max,
                       &total_payment, &overpay);

  ck_assert_ldouble_eq_tol(pay_for_month_min, 509142.86, PREC);
  ck_assert_ldouble_eq_tol(pay_for_month_max, 546857.14, PREC);
  ck_assert_ldouble_eq_tol(total_payment, 3696000.00, PREC);
  ck_assert_ldouble_eq_tol(overpay, 176000, PREC);
}
END_TEST

START_TEST(test_13) {
  long double pay_for_month = 0;
  long double total_payment = 0;
  long double overpay = 0;

  long double credit_amount = 3500000;
  long double month = 7;
  long double interest = 15;

  s21_annuity_calculation(credit_amount, month, interest, &pay_for_month,
                          &total_payment, &overpay);

  ck_assert_ldouble_eq_tol(pay_for_month, 525310.52, PREC);
  ck_assert_ldouble_eq_tol(total_payment, 3677173.64, PREC);
  ck_assert_ldouble_eq_tol(overpay, 177173.64, PREC);
}

START_TEST(test_14) {
  double initial_deposit = 125896;
  int period_in_months = 120;
  double initial_interest = 15;
  int payment_periodicity = 12;
  int is_capitalized = 1;
  double replenishment_amount = 1258;
  double withdraw_amount = 0;
  double tax_interest = 35;
  double accured_interest = 0, tax_amount = 0, deposit_amount = 0;
  s21_deposit_calc(initial_deposit, period_in_months, initial_interest,
                   payment_periodicity, is_capitalized, replenishment_amount,
                   withdraw_amount, tax_interest, &accured_interest,
                   &tax_amount, &deposit_amount);
  ck_assert_double_eq_tol(581112.90, accured_interest, PREC);
  ck_assert_double_eq_tol(203389.51, tax_amount, PREC);
  ck_assert_double_eq_tol(654579.38, deposit_amount, PREC);
}

START_TEST(test_15) {
  double initial_deposit = 45827;
  int period_in_months = 11;
  double initial_interest = 1.5;
  int payment_periodicity = 1;
  int is_capitalized = 0;
  double replenishment_amount = 15288;
  double withdraw_amount = 15;
  double tax_interest = 38;
  double accured_interest = 0, tax_amount = 0, deposit_amount = 0;
  s21_deposit_calc(initial_deposit, period_in_months, initial_interest,
                   payment_periodicity, is_capitalized, replenishment_amount,
                   withdraw_amount, tax_interest, &accured_interest,
                   &tax_amount, &deposit_amount);
  ck_assert_double_eq_tol(1680.14, accured_interest, PREC);
  ck_assert_double_eq_tol(638.45, tax_amount, PREC);
  ck_assert_double_eq_tol(214871.69, deposit_amount, PREC);
}

START_TEST(test_16) {
  double initial_deposit = 4582;
  int period_in_months = 11;
  double initial_interest = 1.5;
  int payment_periodicity = 1;
  int is_capitalized = 1;
  double replenishment_amount = 15288;
  double withdraw_amount = 15;
  double tax_interest = 38;
  double accured_interest = 0, tax_amount = 0, deposit_amount = 0;
  s21_deposit_calc(initial_deposit, period_in_months, initial_interest,
                   payment_periodicity, is_capitalized, replenishment_amount,
                   withdraw_amount, tax_interest, &accured_interest,
                   &tax_amount, &deposit_amount);
  ck_assert_double_eq_tol(1117.36, accured_interest, PREC);
  ck_assert_double_eq_tol(424.60, tax_amount, PREC);
  ck_assert_double_eq_tol(173277.77, deposit_amount, PREC);
}

START_TEST(test_17) {
  double initial_deposit = 200000;
  int period_in_months = 48;
  double initial_interest = 7;
  int payment_periodicity = 12;
  int is_capitalized = 1;
  double replenishment_amount = 1000;
  double withdraw_amount = 10;
  double tax_interest = 22;
  double accured_interest = 0;
  double tax_amount = 0;
  double deposit_amount = 0;
  s21_deposit_calc(initial_deposit, period_in_months, initial_interest,
                   payment_periodicity, is_capitalized, replenishment_amount,
                   withdraw_amount, tax_interest, &accured_interest,
                   &tax_amount, &deposit_amount);

  ck_assert_ldouble_eq_tol(tax_amount, 15569.464546, PREC);
  ck_assert_ldouble_eq_tol(accured_interest, 70770.293389, PREC);
  ck_assert_ldouble_eq_tol(deposit_amount, 302720.828843, PREC);
}

START_TEST(test_18) {
  double initial_deposit = 200000;
  int period_in_months = 8;
  double initial_interest = 7;
  int payment_periodicity = 12;
  int is_capitalized = 1;
  double replenishment_amount = 1000;
  double withdraw_amount = 10;
  double tax_interest = 22;
  double accured_interest = 0;
  double tax_amount = 0;
  double deposit_amount = 0;
  int status = s21_deposit_calc(
      initial_deposit, period_in_months, initial_interest, payment_periodicity,
      is_capitalized, replenishment_amount, withdraw_amount, tax_interest,
      &accured_interest, &tax_amount, &deposit_amount);
  ck_assert_int_eq(FAIL, status);
  ck_assert_ldouble_eq_tol(tax_amount, 0, PREC);
  ck_assert_ldouble_eq_tol(accured_interest, 0, PREC);
  ck_assert_ldouble_eq_tol(deposit_amount, 0, PREC);
}

START_TEST(test_19) {
  double initial_deposit = 3000;
  int period_in_months = 12;
  double initial_interest = 3;
  int payment_periodicity = 1;
  int is_capitalized = 1;
  double replenishment_amount = 500;
  double withdraw_amount = 0;
  double tax_interest = 20;
  double accured_interest = 0;
  double tax_amount = 0;
  double deposit_amount = 0;
  s21_deposit_calc(initial_deposit, period_in_months, initial_interest,
                   payment_periodicity, is_capitalized, replenishment_amount,
                   withdraw_amount, tax_interest, &accured_interest,
                   &tax_amount, &deposit_amount);
  ck_assert_ldouble_eq_tol(deposit_amount, 9139.551403, PREC);
  ck_assert_ldouble_eq_tol(tax_amount, 34.887851, PREC);
  ck_assert_ldouble_eq_tol(accured_interest, 174.439253, PREC);
}

START_TEST(test_20) {
  double initial_deposit = 10000;
  int period_in_months = 10;
  double initial_interest = 5;
  int payment_periodicity = 1;
  int is_capitalized = 0;
  double replenishment_amount = 2000;
  double withdraw_amount = 0;
  double tax_interest = 15;
  double accured_interest = 0;
  double tax_amount = 0;
  double deposit_amount = 0;
  s21_deposit_calc(initial_deposit, period_in_months, initial_interest,
                   payment_periodicity, is_capitalized, replenishment_amount,
                   withdraw_amount, tax_interest, &accured_interest,
                   &tax_amount, &deposit_amount);
  ck_assert_ldouble_eq_tol(deposit_amount, 30672.916667, PREC);
  ck_assert_ldouble_eq_tol(tax_amount, 118.75000, PREC);
  ck_assert_ldouble_eq_tol(accured_interest, 791.666667, PREC);
}

START_TEST(test_21) {
  double initial_deposit = 5000;
  int period_in_months = 24;
  double initial_interest = 5;
  int payment_periodicity = 12;
  int is_capitalized = 0;
  double replenishment_amount = 200;
  double withdraw_amount = 50;
  double tax_interest = 15;
  double accured_interest = 0;
  double tax_amount = 0;
  double deposit_amount = 0;
  s21_deposit_calc(initial_deposit, period_in_months, initial_interest,
                   payment_periodicity, is_capitalized, replenishment_amount,
                   withdraw_amount, tax_interest, &accured_interest,
                   &tax_amount, &deposit_amount);

  ck_assert_ldouble_eq_tol(tax_amount, 113.250000, PREC);
  ck_assert_ldouble_eq_tol(accured_interest, 755.000000, PREC);
  ck_assert_ldouble_eq_tol(deposit_amount, 9241.750000, PREC);
}

Suite *additional_suite(void) {
  Suite *s;
  TCase *tc_calculate_tests;

  s = suite_create("Calculate Tests");
  tc_calculate_tests = tcase_create("Core");

  tcase_add_test(tc_calculate_tests, test_1);
  tcase_add_test(tc_calculate_tests, test_2);
  tcase_add_test(tc_calculate_tests, test_3);
  tcase_add_test(tc_calculate_tests, test_4);
  tcase_add_test(tc_calculate_tests, test_5);
  tcase_add_test(tc_calculate_tests, test_6);
  tcase_add_test(tc_calculate_tests, test_7);
  tcase_add_test(tc_calculate_tests, test_8);
  tcase_add_test(tc_calculate_tests, test_9);
  tcase_add_test(tc_calculate_tests, test_10);
  tcase_add_test(tc_calculate_tests, test_11);
  tcase_add_test(tc_calculate_tests, test_12);
  tcase_add_test(tc_calculate_tests, test_13);
  tcase_add_test(tc_calculate_tests, test_14);
  tcase_add_test(tc_calculate_tests, test_15);
  tcase_add_test(tc_calculate_tests, test_16);
  tcase_add_test(tc_calculate_tests, test_17);
  tcase_add_test(tc_calculate_tests, test_18);
  tcase_add_test(tc_calculate_tests, test_19);
  tcase_add_test(tc_calculate_tests, test_20);
  tcase_add_test(tc_calculate_tests, test_21);

  suite_add_tcase(s, tc_calculate_tests);

  return s;
}

int main(void) {
  int num_failed;
  Suite *s, *calculate;
  SRunner *sr;

  s = s21_suite();
  calculate = additional_suite();

  sr = srunner_create(s);
  srunner_add_suite(sr, calculate);

  srunner_run_all(sr, CK_NORMAL);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
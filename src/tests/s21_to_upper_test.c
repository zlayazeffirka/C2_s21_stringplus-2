#include "s21_tests_main.h"

START_TEST(common_test) {
  char *str = (char *)s21_to_upper("Hello");

  ck_assert_str_eq("HELLO", str);
  free(str);
}
END_TEST

START_TEST(corner_test_return_NULL) {
  char *str = (char *)s21_to_upper(NULL);
  if (str) {
    ck_assert_ptr_nonnull(str);
    free(str);
  }
  ck_assert_ptr_null(str);
}
END_TEST

START_TEST(corner_test) {
  char *str = (char *)s21_to_upper("mem!");

  ck_assert_str_eq("MEM!", str);
  free(str);
}
END_TEST

Suite *s21_to_upper_test(void) {
  Suite *s;
  TCase *tc_s21_to_upper;

  s = suite_create("\033[34m \033[46m #UPPER TESTS \033[0m");

  tc_s21_to_upper = tcase_create("s21_to_upper");
  tcase_add_test(tc_s21_to_upper, common_test);
  tcase_add_test(tc_s21_to_upper, corner_test_return_NULL);
  tcase_add_test(tc_s21_to_upper, corner_test);
  suite_add_tcase(s, tc_s21_to_upper);
  return s;
}

#include "s21_tests_main.h"

START_TEST(common_test) {
  char *str = (char *)s21_to_lower("HELLO");

  ck_assert_str_eq("hello", str);
  free(str);
}
END_TEST

START_TEST(corner_test_return_NULL) {
  char *str = (char *)s21_to_lower(NULL);
  if (str) {
    ck_assert_ptr_nonnull(str);
    free(str);
  }
  ck_assert_ptr_null(str);
}
END_TEST

START_TEST(corner_test) {
  char *str = (char *)s21_to_lower("MEM!");

  ck_assert_str_eq("mem!", str);
  free(str);
}
END_TEST

START_TEST(lowcase_test) {
  char *str = (char *)s21_to_lower("lower simple string");

  ck_assert_str_eq("lower simple string", str);
  free(str);
}
END_TEST

Suite *s21_to_lower_test(void) {
  Suite *s;
  TCase *tc_s21_to_lower;

  s = suite_create("\033[34m \033[46m #LOWER TESTS \033[0m");
  tc_s21_to_lower = tcase_create("s21_to_lower");

  tcase_add_test(tc_s21_to_lower, common_test);
  tcase_add_test(tc_s21_to_lower, corner_test_return_NULL);
  tcase_add_test(tc_s21_to_lower, corner_test);
  tcase_add_test(tc_s21_to_lower, lowcase_test);
  suite_add_tcase(s, tc_s21_to_lower);

  return s;
}

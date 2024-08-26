#include "s21_tests_main.h"
START_TEST(test_strncmp_basic) {
  const char *str1 = "Hello";
  const char *str2 = "Hello";

  int result1 = strncmp(str1, str2, 5);
  int result2 = s21_strncmp(str1, str2, 5);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_empty) {
  const char *str1 = "";
  const char *str2 = "";

  int result1 = strncmp(str1, str2, 0);
  int result2 = s21_strncmp(str1, str2, 0);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_equal_prefix) {
  const char *str1 = "Hello";
  const char *str2 = "Hello World";

  int result1 = strncmp(str1, str2, 5);
  int result2 = s21_strncmp(str1, str2, 5);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_equal_prefix_1) {
  const char *str1 = "Hellooooomazafaka";
  const char *str2 = "Hello World dick";

  ck_assert_int_eq(s21_strncmp(str1, str2, 5), 0);
  ck_assert_int_gt(s21_strncmp(str1, str2, 15), 0);
  ck_assert_int_eq(s21_strncmp(NULL, NULL, 0), 0);
}
END_TEST

Suite *s21_strncmp_test(void) {
  Suite *s;
  TCase *tc_s21_strncmp;
  s = suite_create("\033[34m \033[46m STRNCMP TESTS \033[0m");

  tc_s21_strncmp = tcase_create("s21_strncmp");

  tcase_add_test(tc_s21_strncmp, test_strncmp_basic);
  tcase_add_test(tc_s21_strncmp, test_strncmp_empty);
  tcase_add_test(tc_s21_strncmp, test_strncmp_equal_prefix);
  tcase_add_test(tc_s21_strncmp, test_strncmp_equal_prefix_1);

  suite_add_tcase(s, tc_s21_strncmp);

  return s;
}
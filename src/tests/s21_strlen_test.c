#include "s21_tests_main.h"

START_TEST(strlen_test_1) {
  const char* str = "Hello, World!";
  size_t result_original = strlen(str);
  size_t result_custom = s21_strlen(str);
  ck_assert_int_eq(result_original, result_custom);
}
END_TEST

START_TEST(strlen_test_2) {
  const char* str = "";
  size_t result_original = strlen(str);
  size_t result_custom = s21_strlen(str);
  ck_assert_int_eq(result_original, result_custom);
}
END_TEST

START_TEST(strlen_test_3) {
  const char* str = "12345";
  size_t result_original = strlen(str);
  size_t result_custom = s21_strlen(str);
  ck_assert_int_eq(result_original, result_custom);
}
END_TEST

START_TEST(strlen_test_4) {
  const char* str = "!@#$%^&*()";
  size_t result_original = strlen(str);
  size_t result_custom = s21_strlen(str);
  ck_assert_int_eq(result_original, result_custom);
}
END_TEST

START_TEST(strlen_test_5) {
  const char* str =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
      "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

  size_t result_original = strlen(str);
  size_t result_custom = s21_strlen(str);
  ck_assert_int_eq(result_original, result_custom);
}
END_TEST

Suite* s21_strlen_test(void) {
  Suite* s;
  TCase* tc_s21_strlen;
  s = suite_create("\033[34m \033[46m STRLEN TESTS \033[0m");

  tc_s21_strlen = tcase_create("s21_strlen");
  tcase_add_test(tc_s21_strlen, strlen_test_1);
  tcase_add_test(tc_s21_strlen, strlen_test_2);
  tcase_add_test(tc_s21_strlen, strlen_test_3);
  tcase_add_test(tc_s21_strlen, strlen_test_4);
  tcase_add_test(tc_s21_strlen, strlen_test_5);
  suite_add_tcase(s, tc_s21_strlen);
  return s;
}
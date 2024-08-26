#include "s21_tests_main.h"

START_TEST(test_trim_spaces) {
  const char *original = "   Hello, World!   ";
  const char *to_trim = " ";
  char *result = s21_trim(original, to_trim);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(test_trim_characters_in_middle) {
  const char *original = "perKeep This Trimmedper";
  const char *to_trim = "per";
  char *result = s21_trim(original, to_trim);
  ck_assert_str_eq(result, "Keep This Trimmed");
  free(result);
}
END_TEST

START_TEST(test_trim_null_pointers) {
  const char *original = NULL;
  const char *to_trim = NULL;
  char *result = s21_trim(original, to_trim);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_no_matching_characters) {
  const char *original = "No Trimming Here!";
  const char *to_trim = "-";
  char *result = s21_trim(original, to_trim);
  ck_assert_str_eq(result, "No Trimming Here!");
  free(result);
}
END_TEST

Suite *s21_trim_test(void) {
  Suite *s = suite_create("\033[34m \033[46m #TRIM TESTS \033[0m");
  TCase *tc_s21_trim = tcase_create("s21_trim");

  tcase_add_test(tc_s21_trim, test_trim_spaces);
  tcase_add_test(tc_s21_trim, test_trim_characters_in_middle);
  tcase_add_test(tc_s21_trim, test_trim_null_pointers);
  tcase_add_test(tc_s21_trim, test_trim_no_matching_characters);
  suite_add_tcase(s, tc_s21_trim);
  return s;
}
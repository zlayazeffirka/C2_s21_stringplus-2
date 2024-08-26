#include "s21_tests_main.h"

START_TEST(strstr_eq_test) {
  const char* haystack = "Testing strstr implementation";
  const char* needle = "str";

  char* result_original = strstr(haystack, needle);
  char* result_custom = s21_strstr(haystack, needle);
  ck_assert_str_eq(result_original, result_custom);
}
END_TEST

START_TEST(strstr_eq_test_2) {
  const char* haystack = "This is another example for testing";
  const char* needle = "another";

  char* result_original = strstr(haystack, needle);
  char* result_custom = s21_strstr(haystack, needle);
  ck_assert_str_eq(result_original, result_custom);
}
END_TEST

START_TEST(strstr_eq_test_3) {
  const char* haystack = "12345";
  const char* needle = "34";

  char* result_original = strstr(haystack, needle);
  char* result_custom = s21_strstr(haystack, needle);
  ck_assert_str_eq(result_original, result_custom);
}
END_TEST

START_TEST(strstr_eq_test_4) {
  const char* haystack = "NoMatches";
  const char* needle = "xyz";

  char* result_original = strstr(haystack, needle);
  char* result_custom = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(result_original, result_custom);
}
END_TEST

START_TEST(strstr_eq_test_5) {
  const char* haystack = "AABBAABB";
  const char* needle = "BB";

  char* result_original = strstr(haystack, needle);
  char* result_custom = s21_strstr(haystack, needle);
  ck_assert_str_eq(result_original, result_custom);
}
END_TEST

Suite* s21_strstr_test(void) {
  Suite* s;
  TCase* tc_s21_strstr;
  s = suite_create("\033[34m \033[46m STRSTR TESTS \033[0m");

  tc_s21_strstr = tcase_create("s21_strstr");
  tcase_add_test(tc_s21_strstr, strstr_eq_test);
  tcase_add_test(tc_s21_strstr, strstr_eq_test_2);
  tcase_add_test(tc_s21_strstr, strstr_eq_test_3);
  tcase_add_test(tc_s21_strstr, strstr_eq_test_4);
  tcase_add_test(tc_s21_strstr, strstr_eq_test_5);
  suite_add_tcase(s, tc_s21_strstr);
  return s;
}
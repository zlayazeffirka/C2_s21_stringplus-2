#include "s21_tests_main.h"

START_TEST(strrchr_advanced_test) {
  const char* str = "This is a more advanced test for strrchr implementation";
  int target = 'a';

  char* result_original = strrchr(str, target);
  char* result_custom = s21_strrchr(str, target);
  ck_assert_str_eq(result_original, result_custom);
}
END_TEST

START_TEST(strrchr_advanced_test_2) {
  const char* str = "Strrchr is a useful function for string manipulation";
  int target = 't';

  char* result_original = strrchr(str, target);
  char* result_custom = s21_strrchr(str, target);
  ck_assert_str_eq(result_original, result_custom);
}

START_TEST(strrchr_advanced_test_3) {
  const char* str = "No target here!";
  int target = 'x';

  char* result_original = strrchr(str, target);
  char* result_custom = s21_strrchr(str, target);
  ck_assert_ptr_eq(result_original, result_custom);
}
END_TEST

Suite* s21_strrchr_test(void) {
  Suite* s;
  TCase* tc_s21_strrchr;
  s = suite_create("\033[34m \033[46m STRRCHR TESTS \033[0m");

  tc_s21_strrchr = tcase_create("s21_strrchr");
  tcase_add_test(tc_s21_strrchr, strrchr_advanced_test);
  tcase_add_test(tc_s21_strrchr, strrchr_advanced_test_2);
  tcase_add_test(tc_s21_strrchr, strrchr_advanced_test_3);

  suite_add_tcase(s, tc_s21_strrchr);

  return s;
}
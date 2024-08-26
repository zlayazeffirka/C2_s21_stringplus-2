#include "s21_tests_main.h"

START_TEST(common_test) {
  const char* str1 = "Hello";
  const char* str2 = "l";
  ck_assert_uint_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(many_set_test) {
  const char* str1 = "HelloWorld";
  const char* str2 = "jW";
  ck_assert_uint_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(same_pattern_in_stroke_test) {
  const char* str1 = "HelloHelloHello";
  const char* str2 = "o";
  ck_assert_uint_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(null_prefix_test) {
  const char* str1 = "HelloHelloHello";
  const char* str2 = "H";
  ck_assert_uint_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(incorrect_prefix_test) {
  const char* str1 = "HelloHelloHello";
  const char* str2 = "";
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(incorrect_str_test) {
  const char* str1 = "";
  const char* str2 = "f";
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

Suite* s21_strcspn_test(void) {
  Suite* s;
  TCase* tc_s21_strcspn;
  s = suite_create("\033[34m \033[46m STRCSPN TESTS \033[0m");

  tc_s21_strcspn = tcase_create("s21_strcspn");
  tcase_add_test(tc_s21_strcspn, common_test);
  tcase_add_test(tc_s21_strcspn, many_set_test);
  tcase_add_test(tc_s21_strcspn, same_pattern_in_stroke_test);
  tcase_add_test(tc_s21_strcspn, null_prefix_test);
  tcase_add_test(tc_s21_strcspn, incorrect_prefix_test);
  tcase_add_test(tc_s21_strcspn, incorrect_str_test);
  suite_add_tcase(s, tc_s21_strcspn);
  return s;
}
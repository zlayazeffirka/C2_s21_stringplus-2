#include "s21_tests_main.h"

START_TEST(str_eq_test_1) {
  const char* str1 = "Programming is fun!";
  const char* str2 = "amiug";

  ck_assert_str_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}

START_TEST(str_eq_test_2) {
  const char* str1 = "Hello, World!";
  const char* str2 = "aeiou";

  ck_assert_str_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}

START_TEST(str_eq_test_3) {
  const char* str1 = "1234567890";
  const char* str2 = "aeiou";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}

START_TEST(str_eq_test_4) {
  const char* str1 = "Testing 123";
  const char* str2 = "xy z";

  ck_assert_str_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}

START_TEST(str_eq_test_5) {
  const char* str1 = "NoMatchxes";
  const char* str2 = "xyz";

  ck_assert_str_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

Suite* s21_strpbrk_test(void) {
  Suite* s;
  TCase* tc_s21_strpbrk;
  s = suite_create("\033[34m \033[46m STRPBRK TESTS \033[0m");

  tc_s21_strpbrk = tcase_create("s21_strpbrk");
  tcase_add_test(tc_s21_strpbrk, str_eq_test_1);
  tcase_add_test(tc_s21_strpbrk, str_eq_test_2);
  tcase_add_test(tc_s21_strpbrk, str_eq_test_3);
  tcase_add_test(tc_s21_strpbrk, str_eq_test_4);
  tcase_add_test(tc_s21_strpbrk, str_eq_test_5);
  suite_add_tcase(s, tc_s21_strpbrk);
  return s;
}

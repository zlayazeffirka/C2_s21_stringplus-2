#include "s21_tests_main.h"

START_TEST(int_eq_test) {
  char* str = "(char *)malloc(10)";
  char* str_1 = "(char *)malloc(10)";

  ck_assert_int_eq(memcmp(str, str_1, 5), s21_memcmp(str, str_1, 5));
}
END_TEST

START_TEST(str1_more_than_str2_test) {
  char* str = "(char *)malloc(10)";
  char* str_1 = "(char *)";

  ck_assert_int_eq(memcmp(str, str_1, 9), s21_memcmp(str, str_1, 9));
}
END_TEST

START_TEST(none_valid_size_t_test) {
  char* str = "(char *)malloc(10)";
  char* str_1 = "(char *)malloc(10)";

  ck_assert_int_eq(memcmp(str, str_1, 0), s21_memcmp(str, str_1, 0));
}
END_TEST

START_TEST(str1_longer_than_str2) {
  char* str = "(char *)";
  char* str_1 = "(char *)malloc(10)";

  ck_assert_int_eq(memcmp(str, str_1, 9), s21_memcmp(str, str_1, 9));
  ck_assert_msg(memcmp(str, str_1, 9) < 0,
                "returning value more or equal than 0");
  ck_assert_msg(s21_memcmp(str, str_1, 9) < 0,
                "returning value more or equal than 0");
}
END_TEST

Suite* s21_memcmp_test(void) {
  Suite* s;
  TCase* tc_s21_memcmp;
  s = suite_create("\033[34m \033[46m MEMCMP TESTS \033[0m");

  tc_s21_memcmp = tcase_create("s21_memcmp");
  tcase_add_test(tc_s21_memcmp, int_eq_test);
  tcase_add_test(tc_s21_memcmp, str1_more_than_str2_test);
  tcase_add_test(tc_s21_memcmp, none_valid_size_t_test);
  tcase_add_test(tc_s21_memcmp, str1_longer_than_str2);
  suite_add_tcase(s, tc_s21_memcmp);
  return s;
}
#include "s21_tests_main.h"

START_TEST(str_eq_test) {
  char dest[10];
  char s21_dest[10];
  char* src = "hello";
  char* s21_src = "hello";

  ck_assert_str_eq(strncpy(dest, src, 10), s21_strncpy(s21_dest, s21_src, 10));
}
END_TEST

START_TEST(n_is_null_test) {
  char* dest = (char*)malloc(10);
  char* s21_dest = (char*)malloc(10);
  const char* src = "hello";
  const char* s21_src = "hello";

  ck_assert_ptr_eq(strncpy(dest, src, 3), dest);
  ck_assert_ptr_eq(s21_strncpy(s21_dest, s21_src, 3), s21_dest);

  free(dest);
  free(s21_dest);
}
END_TEST

START_TEST(dest_overload_test) {
  char* dest = (char*)malloc(20);
  char* s21_dest = (char*)malloc(20);
  const char* src = "hello";
  const char* s21_src = "hello";

  ck_assert_str_eq(strncpy(dest, src, 20), s21_strncpy(s21_dest, s21_src, 20));

  free(dest);
  free(s21_dest);
}
END_TEST

Suite* s21_strncpy_test(void) {
  Suite* s;
  TCase* tc_s21_strncpy;
  s = suite_create("\033[34m \033[46m STRNCPY TESTS \033[0m");

  tc_s21_strncpy = tcase_create("s21_strncpy");

  tcase_add_test(tc_s21_strncpy, str_eq_test);
  tcase_add_test(tc_s21_strncpy, n_is_null_test);
  tcase_add_test(tc_s21_strncpy, dest_overload_test);

  suite_add_tcase(s, tc_s21_strncpy);

  return s;
}

#include "s21_tests_main.h"

START_TEST(str_eq_test) {
  char str[10] = {'\0'};
  char str_1[10] = {'\0'};

  ck_assert_str_eq((char*)memset(str_1, 6, 9), (char*)s21_memset(str, 6, 9));
}
END_TEST

START_TEST(fiil_one_byte_test) {
  char* str_1 = (char*)malloc(10);

  ck_assert_ptr_eq(memset(str_1, 6, 10), s21_memset(str_1, 6, 10));

  free(str_1);
}
END_TEST

Suite* s21_memset_test(void) {
  Suite* s;
  TCase* tc_s21_memset;
  s = suite_create("\033[34m \033[46m MEMSET TESTS \033[0m");
  tc_s21_memset = tcase_create("s21_memset");

  tcase_add_test(tc_s21_memset, str_eq_test);
  tcase_add_test(tc_s21_memset, fiil_one_byte_test);

  suite_add_tcase(s, tc_s21_memset);

  return s;
}

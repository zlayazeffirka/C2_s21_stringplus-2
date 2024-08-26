#include "s21_tests_main.h"

START_TEST(common_test) {
  char* str = "Hello";
  size_t n = strlen(str);
  char c = 'o';
  ck_assert_ptr_eq(memchr(str, c, n), s21_memchr(str, c, n));
}
END_TEST

START_TEST(null_test) {
  char* str = "Hello";
  size_t n = strlen(str);
  char c = 'b';
  ck_assert_ptr_eq(memchr(str, c, n), s21_memchr(str, c, n));
}
END_TEST

START_TEST(find_space_test) {
  char* str = "Hel l o";
  size_t n = strlen(str);
  char c = ' ';
  ck_assert_ptr_eq(memchr(str, c, n), s21_memchr(str, c, n));
}
END_TEST

START_TEST(str_exists_test) {
  char* str = "Hel";
  size_t n = strlen(str);
  char c = 'v';
  ck_assert_ptr_null(s21_memchr(str, c, n));
}
END_TEST

START_TEST(char_not_found_test) {
  char* str = "Hel";
  size_t n = strlen(str);
  char c = 'H';
  ck_assert_ptr_nonnull(s21_memchr(str, c, n));
}
END_TEST

Suite* s21_memchr_test(void) {
  Suite* s;
  TCase* tc_s21_memchr;

  s = suite_create("\033[34m \033[46m MEMCHR TESTS \033[0m");

  tc_s21_memchr = tcase_create("s21_memchr");
  tcase_add_test(tc_s21_memchr, common_test);
  tcase_add_test(tc_s21_memchr, null_test);
  tcase_add_test(tc_s21_memchr, find_space_test);
  tcase_add_test(tc_s21_memchr, str_exists_test);
  tcase_add_test(tc_s21_memchr, char_not_found_test);
  suite_add_tcase(s, tc_s21_memchr);

  return s;
}

#include "s21_tests_main.h"

START_TEST(base_test) {
  char* str = "Hello";
  char c = '\0';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

START_TEST(check_first_entry_test) {
  char* str = "sukabblyat";
  char c = 'b';
  ck_assert_ptr_eq(str + 4, s21_strchr(str, c));
}
END_TEST

// START_TEST(returning_the_first_char_test) {
//   char* str = "sukabblyat";
//   char c = 's';
//   ck_assert_int_eq(*(str), *s21_strchr(str, c));
//   ck_assert_int_eq(str[0], *strchr(str, c));
// }
// END_TEST

Suite* s21_strchr_test(void) {
  Suite* s;
  TCase* tc_s21_strchr;
  s = suite_create("\033[34m \033[46m STRCHR TESTS \033[0m");

  tc_s21_strchr = tcase_create("s21_strchr");
  tcase_add_test(tc_s21_strchr, base_test);
  tcase_add_test(tc_s21_strchr, check_first_entry_test);
  // tcase_add_test(tc_s21_strchr, returning_the_first_char_test);

  suite_add_tcase(s, tc_s21_strchr);

  return s;
}

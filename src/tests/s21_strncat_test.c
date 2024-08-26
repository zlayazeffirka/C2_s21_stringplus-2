#include "s21_tests_main.h"

START_TEST(base_test) {
  char dist[12] = "Hello";
  const char* src = " Warld";
  char s21_dist[12] = "Hello";
  const char* s21_src = " Warld";

  ck_assert_str_eq(strncat(dist, src, 4), s21_strncat(s21_dist, s21_src, 4));
}
END_TEST

START_TEST(dest_null_test) {
  char dest[12] = "Hello";
  const char* src = " Warld";
  char s21_dest[12] = "Hello";
  const char* s21_src = " Warld";

  ck_assert_str_eq(strncat(dest, src, 0), s21_strncat(s21_dest, s21_src, 0));
}
END_TEST

START_TEST(term_null_endofstr_test) {
  char dest[12] = "Hello";
  const char* src = " Warld";
  char s21_dest[12] = "Hello";
  const char* s21_src = " Warld";

  ck_assert_str_eq(strncat(dest, src, 4), s21_strncat(s21_dest, s21_src, 4));

  char* end = strchr(dest, '\0');
  char* s21_end = strchr(s21_dest, '\0');

  ck_assert_ptr_nonnull(end);
  ck_assert_ptr_nonnull(s21_end);
  ck_assert_int_eq(dest[9], *end);
  ck_assert_int_eq(s21_dest[9], *s21_end);

  ck_assert_ptr_eq(dest + strlen(dest), end);
  ck_assert_ptr_eq(s21_dest + strlen(s21_dest), s21_end);
}
END_TEST

Suite* s21_strncat_test(void) {
  Suite* s;
  TCase* tc_s21_strncat;
  s = suite_create("\033[34m \033[46m STRNCAT TESTS \033[0m");

  tc_s21_strncat = tcase_create("Core");
  tcase_add_test(tc_s21_strncat, base_test);
  tcase_add_test(tc_s21_strncat, dest_null_test);
  tcase_add_test(tc_s21_strncat, term_null_endofstr_test);

  suite_add_tcase(s, tc_s21_strncat);

  return s;
}

#include "s21_tests_main.h"

START_TEST(str_eq_test) {
#ifdef __APPLE__
  ck_assert_str_eq(strerror(errno), s21_strerror(errno));
#elif __linux__
  ck_assert_str_eq(strerror(2), s21_strerror(2));
#endif
}
END_TEST

START_TEST(S21_STRERROR) {
  char *err1 = s21_strerror(0);
  char *err2 = strerror(0);
  ck_assert_int_eq(strcmp(err1, err2), 0);
  char *err3 = s21_strerror(106);
  char *err4 = strerror(106);
  ck_assert_int_eq(strcmp(err3, err4), 0);
}

START_TEST(all_of_errors_codes_test) {
  for (int i = 1; i < 40; i++) ck_assert_str_eq(strerror(i), s21_strerror(i));
}
END_TEST

START_TEST(unknown_error) {
  char *err1 = s21_strerror(404);
  char *err2 = strerror(404);
  ck_assert_str_eq(err1, err2);
  free(err2);
}
END_TEST

Suite *s21_strerror_test(void) {
  Suite *s;
  TCase *tc_s21_strerror;
  s = suite_create("\033[34m \033[46m STRERROR TESTS \033[0m");

  tc_s21_strerror = tcase_create("s21_strerror");
  tcase_add_test(tc_s21_strerror, str_eq_test);
  tcase_add_test(tc_s21_strerror, S21_STRERROR);
  tcase_add_test(tc_s21_strerror, all_of_errors_codes_test);
  tcase_add_test(tc_s21_strerror, unknown_error);
  suite_add_tcase(s, tc_s21_strerror);

  return s;
}

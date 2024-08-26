#include "s21_tests_main.h"

START_TEST(test_insert_basic) {
  const char *original = "Hello, world!";
  const char *inserted = "beautiful ";
  size_t index = 7;

  char *result = (char *)s21_insert(original, inserted, index);

  ck_assert_str_eq(result, "Hello, beautiful world!");

  free(result);
}
END_TEST

START_TEST(test_insert_at_beginning) {
  const char *original = "world!";
  const char *inserted = "Hello, ";
  size_t index = 0;

  char *result = (char *)s21_insert(original, inserted, index);

  ck_assert_str_eq(result, "Hello, world!");

  free(result);
}
END_TEST

START_TEST(test_insert_at_end) {
  const char *original = "Hello, ";
  const char *inserted = "world!";
  size_t index = 7;

  char *result = (char *)s21_insert(original, inserted, index);

  ck_assert_str_eq(result, "Hello, world!");

  free(result);
}
END_TEST

START_TEST(test_insert_empty_string) {
  const char *original = "Hello, world!";
  const char *inserted = "";
  size_t index = 7;

  char *result = (char *)s21_insert(original, inserted, index);

  ck_assert_str_eq(result, "Hello, world!");

  free(result);
}
END_TEST

START_TEST(test_insert_null_string) {
  const char *original = "Hello, world!";
  const char *inserted = NULL;
  size_t index = 7;

  char *result = (char *)s21_insert(original, inserted, index);

  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_insert_large_start_index) {
  const char *original = "Hello, ";
  const char *inserted = "world!";
  size_t index = 40;

  char *result = (char *)s21_insert(original, inserted, index);

  ck_assert_ptr_null(result);

  free(result);
}
END_TEST

Suite *s21_insert_test(void) {
  Suite *s = suite_create("\033[34m \033[46m #INSERT TESTS \033[0m");
  TCase *tc_s21_insert = tcase_create("s21_insert_test");

  tcase_add_test(tc_s21_insert, test_insert_basic);
  tcase_add_test(tc_s21_insert, test_insert_at_beginning);
  tcase_add_test(tc_s21_insert, test_insert_at_end);
  tcase_add_test(tc_s21_insert, test_insert_empty_string);
  tcase_add_test(tc_s21_insert, test_insert_null_string);
  tcase_add_test(tc_s21_insert, test_insert_large_start_index);

  suite_add_tcase(s, tc_s21_insert);
  return s;
}
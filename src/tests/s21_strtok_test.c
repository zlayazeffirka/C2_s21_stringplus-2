#include "s21_tests_main.h"

// Тест 1: Разделение строки с использованием запятых
START_TEST(test_s21_strtok_basic) {
  char input_str[] = "This,is,a,test,string";
  char delimiters[] = ",";

  char *token = s21_strtok(input_str, delimiters);
  ck_assert_str_eq(token, "This");

  token = s21_strtok(NULL, delimiters);
  ck_assert_str_eq(token, "is");

  token = s21_strtok(NULL, delimiters);
  ck_assert_str_eq(token, "a");
}
END_TEST

// Тест 2: Разделение пустой строки
START_TEST(test_s21_strtok_empty_string) {
  char empty_str[] = "";
  char delimiters[] = ",";

  char *token = s21_strtok(empty_str, delimiters);
  ck_assert_ptr_eq(token, NULL);
}
END_TEST

// Тест 3: Разделение строки с отсутствующими разделителями
START_TEST(test_s21_strtok_no_delimiters) {
  char no_delimiters[] = "NoDelimitersHere";
  char delimiters[] = ",";

  char *token = s21_strtok(no_delimiters, delimiters);
  ck_assert_str_eq(token, no_delimiters);
}
END_TEST

// Тест 4: Разделение строки с измененными разделителями
START_TEST(test_s21_strtok_different_delimiters) {
  char input_str[] = "This|is|a|test|string";
  char different_delimiters[] = "|";

  char *token = s21_strtok(input_str, different_delimiters);
  ck_assert_str_eq(token, "This");

  token = s21_strtok(NULL, different_delimiters);
  ck_assert_str_eq(token, "is");

  token = s21_strtok(NULL, different_delimiters);
  ck_assert_str_eq(token, "a");
}
END_TEST

// Тест 5: Разделение строки с использованием разных разделителей
START_TEST(test_s21_strtok_mixed_delimiters) {
  char input_str[] = "This, is a test; string";
  char mixed_delimiters[] = ",;";

  char *token = s21_strtok(input_str, mixed_delimiters);
  ck_assert_str_eq(token, "This");

  token = s21_strtok(NULL, mixed_delimiters);
  ck_assert_str_eq(token, " is a test");

  token = s21_strtok(NULL, mixed_delimiters);
  ck_assert_str_eq(token, " string");
}
END_TEST

// Тест 6: Разделение строки начинающейся с разделителей
START_TEST(test_s21_strtok_start_with_delimiters) {
  char input_str[] = ",This, is a test, string";
  char strtok_start_with_delimiters[] = ",";

  char *token = s21_strtok(input_str, strtok_start_with_delimiters);
  ck_assert_str_eq(token, "This");

  token = s21_strtok(NULL, strtok_start_with_delimiters);
  ck_assert_str_eq(token, " is a test");

  token = s21_strtok(NULL, strtok_start_with_delimiters);
  ck_assert_str_eq(token, " string");
}
END_TEST

Suite *s21_strtok_test(void) {
  Suite *s;
  TCase *tc_s21_strtok;
  s = suite_create("\033[34m \033[46m STRTOK TESTS \033[0m");

  tc_s21_strtok = tcase_create("s21_strtok");
  tcase_add_test(tc_s21_strtok, test_s21_strtok_basic);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_empty_string);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_no_delimiters);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_different_delimiters);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_mixed_delimiters);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_start_with_delimiters);

  suite_add_tcase(s, tc_s21_strtok);

  return s;
}
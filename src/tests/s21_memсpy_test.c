#include "s21_tests_main.h"

START_TEST(test_memcpy_basic) {
  char src[] = "Hello";
  char dest1[10] = "";
  char dest2[10] = "";

  memcpy(dest1, src, 5);
  s21_memcpy(dest2, src, 5);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_memcpy_empty) {
  char src[] = "";
  char dest1[10] = "12345";
  char dest2[10] = "12345";

  memcpy(dest1, src, 0);
  s21_memcpy(dest2, src, 0);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_memcpy_large) {
  char src[10000];
  char dest1[10000];
  char dest2[10000];

  for (int i = 0; i < 10000; ++i) {
    src[i] = (char)(i % 256);
    dest1[i] = 0;
    dest2[i] = 0;
  }

  memcpy(dest1, src, 10000);
  s21_memcpy(dest2, src, 10000);

  ck_assert_mem_eq(dest1, dest2, 10000);
}
END_TEST

START_TEST(test_memcpy_overlap) {
  char src[] = "Hello";
  char dest1[10] = "12345";
  char dest2[10] = "12345";

  memcpy(dest1 + 2, src, 3);
  s21_memcpy(dest2 + 2, src, 3);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_memcpy_return_value) {
  char src[] = "Hello";
  char dest1[10] = "";
  char dest2[10] = "";

  char *result1 = memcpy(dest1, src, 5);
  char *result2 = s21_memcpy(dest2, src, 5);

  ck_assert_ptr_eq(result1, dest1);
  ck_assert_ptr_eq(result2, dest2);
}
END_TEST

START_TEST(test_memcpy_no_overlap) {
  const char *src = "Hello";
  char dest[10] = "12345";

  memcpy(dest, src, 5);
  s21_memcpy(dest, src, 5);

  ck_assert_mem_eq(dest, src, 5);
}
END_TEST

START_TEST(test_memcpy_zero_size) {
  const char *src = "Hello";
  char dest[10] = "12345";

  memcpy(dest + 2, src, 0);
  s21_memcpy(dest + 2, src, 0);

  ck_assert_mem_eq(dest, "12345", 5);
}
END_TEST

START_TEST(test_memcpy_reverse_copy) {
  const char *src = "Hello";
  char dest1[10] = "12345";
  char dest2[10] = "12345";

  memcpy(dest1 + 2, src, 3);
  s21_memcpy(dest2 + 2, src, 3);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

Suite *s21_memcpy_test(void) {
  Suite *s;
  TCase *tc_s21_memcpy;
  s = suite_create("\033[34m \033[46m MEMCPY TESTS \033[0m");

  tc_s21_memcpy = tcase_create("s21_memcpy");
  tcase_add_test(tc_s21_memcpy, test_memcpy_basic);
  tcase_add_test(tc_s21_memcpy, test_memcpy_empty);
  tcase_add_test(tc_s21_memcpy, test_memcpy_large);
  tcase_add_test(tc_s21_memcpy, test_memcpy_overlap);
  tcase_add_test(tc_s21_memcpy, test_memcpy_no_overlap);
  tcase_add_test(tc_s21_memcpy, test_memcpy_zero_size);
  tcase_add_test(tc_s21_memcpy, test_memcpy_return_value);
  tcase_add_test(tc_s21_memcpy, test_memcpy_reverse_copy);

  suite_add_tcase(s, tc_s21_memcpy);
  return s;
}

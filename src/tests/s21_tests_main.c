#include "s21_tests_main.h"

int main() {
  int failed_count = 0;
  Suite *s21_string_suite_create[] = {
      s21_memchr_test(),   s21_memcmp_test(),   s21_memcpy_test(),
      s21_memset_test(),   s21_strncat_test(),  s21_strchr_test(),
      s21_strncmp_test(),  s21_strncpy_test(),  s21_strcspn_test(),
      s21_strerror_test(), s21_strlen_test(),   s21_strpbrk_test(),
      s21_strrchr_test(),  s21_strstr_test(),   s21_strtok_test(),
      s21_sprintf_test(),  s21_to_upper_test(), s21_to_lower_test(),
      s21_insert_test(),   s21_trim_test(),     NULL};

  for (int i = 0; s21_string_suite_create[i] != NULL; i++) {
    SRunner *suite_runner = srunner_create(s21_string_suite_create[i]);

    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_run_all(suite_runner, CK_NORMAL);

    failed_count += srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }

  printf("\033[%dm FAILED: %d \033[0m \n", failed_count ? 41 : 42,
         failed_count);

  return (failed_count == 0) ? 0 : 1;
}

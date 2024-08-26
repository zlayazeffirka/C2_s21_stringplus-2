#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t s1_len = s21_strlen(str1), s2_len = s21_strlen(str2);
  s21_size_t i = 0;
  int flag = 0;

  while (i < s1_len && !flag) {
    for (s21_size_t j = 0; j < s2_len; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
      }
    }
    if (!flag) {
      i++;
    }
  }
  return i;
}
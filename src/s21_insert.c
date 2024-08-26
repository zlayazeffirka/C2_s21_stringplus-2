#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) {
    return S21_NULL;
  }
  s21_size_t len_src = s21_strlen(src);
  if (start_index > s21_strlen(src)) {
    return S21_NULL;
  }
  s21_size_t len_str = s21_strlen(str);
  char *res = (char *)calloc(len_src + len_str + 1, sizeof(char));
  s21_strncpy(res, src, start_index);
  s21_strncpy(res + start_index, str, len_str);
  s21_strncpy(res + start_index + len_str, src + start_index,
              len_src - start_index);
  return res;
}
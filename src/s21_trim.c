#include "s21_string.h"

int is_in(const char *str, char c) {
  int res = 0;
  for (const char *ptr = str; *ptr && !res; ptr++) {
    if (c == *ptr) {
      res = 1;
    }
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) {
    return S21_NULL;
  }
  s21_size_t len = s21_strlen(src);
  s21_size_t left_start = 0, right_start = len - 1;
  short left = 0, right = 0;
  for (s21_size_t i = 0; src[i] && !(left & right); ++i) {
    if (!is_in(trim_chars, src[i]) && !left) {
      left_start = i;
      left = 1;
    }
    if (!is_in(trim_chars, src[len - i - 1]) && !right) {
      right_start = len - i - 1;
      right = 1;
    }
  }
  char *res;
  if (right_start < left_start) {
    res = (char *)calloc(1, sizeof(char));
  } else {
    res = (char *)calloc(right_start - left_start + 2, sizeof(char));
    s21_strncpy(res, src + left_start, right_start - left_start + 1);
  }
  return res;
}
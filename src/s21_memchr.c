#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  void *ptr = S21_NULL;
  s21_size_t i = 0;

  while (i < n && !ptr) {
    if (s[i] == c) {
      ptr = &s[i];
    }
    i++;
  }
  return ptr;
}
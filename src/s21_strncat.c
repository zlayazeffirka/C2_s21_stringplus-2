#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest), src_len = s21_strlen(src);
  s21_size_t i = 0;

  while (i < n && i < src_len) {
    dest[dest_len + i] = src[i];
    i++;
  }
  dest[dest_len + i] = '\0';

  return dest;
}
#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  if (!str) {
    return S21_NULL;
  }
  char *res = S21_NULL;
  long long i = s21_strlen(str);
  for (; i >= 0 && str[i] != (char)c; i--) {
  }
  if (i > -1) {
    res = (char *)str + i;
  }
  return res;
}
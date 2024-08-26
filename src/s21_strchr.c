#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  if (!str) {
    return S21_NULL;
  }
  const char *ptr = str;
  for (; *ptr && *ptr != (char)c; ptr++) {
  }
  if (!*ptr && (char)c != '\0') {
    ptr = S21_NULL;
  }
  return (char *)ptr;
}
#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  if (!str) {
    return 0;
  }
  const char *ptr = str;
  for (; *ptr; ptr++) {
  }
  return (s21_size_t)(ptr - str);
}
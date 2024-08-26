#include "s21_string.h"

void *s21_to_lower(const char *str) {
  if (!str) {
    return S21_NULL;
  }
  s21_size_t len = s21_strlen(str);
  char *res = (char *)calloc(len + 1, sizeof(char));
  if (res) {
    for (s21_size_t i = 0; i < len; ++i) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        res[i] = str[i] - 'A' + 'a';
      } else {
        res[i] = str[i];
      }
    }
  } else {
    res = S21_NULL;
  }
  return res;
}
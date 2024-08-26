#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *ptr;
  char *res = S21_NULL;
  if (str) {
    ptr = str;
  }
  if (!ptr || s21_strlen(ptr) == 0) {
    return res;
  }
  char *str_ptr = ptr;
  char *k = s21_strchr(delim, *str_ptr);
  while (k) {
    str_ptr++;
    k = s21_strchr(delim, *str_ptr);
  }
  if (!(*str_ptr)) {
    res = S21_NULL;
  } else {
    char *token_begin = str_ptr;
    while (*str_ptr && !k) {
      str_ptr++;
      k = s21_strchr(delim, *str_ptr);
    }
    if (!(*str_ptr)) {
      ptr = str_ptr;
      res = token_begin;
    } else {
      *str_ptr = '\0';
      ptr = str_ptr + 1;
      res = token_begin;
    }
  }
  return res;
}
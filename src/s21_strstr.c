#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (!needle) {
    return (char *)haystack;
  }
  if (!haystack) {
    return S21_NULL;
  }
  s21_size_t needle_len = s21_strlen(needle);
  const char *hptr = haystack;
  int flag = 1;
  while (*hptr && flag) {
    if (*needle == *hptr) {
      if (!s21_strncmp(hptr, needle, needle_len)) {
        flag = 0;
      }
    }
    if (flag) {
      hptr++;
    }
  }
  if (flag) {
    hptr = S21_NULL;
  }
  return (char *)hptr;
}
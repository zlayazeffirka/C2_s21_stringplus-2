#include "s21_string.h"

int s21_memcmp(const void* ptr1, const void* ptr2, s21_size_t n) {
  int result = 0;
  if (n != 0) {
    unsigned char *p1 = (unsigned char*)ptr1, *p2 = (unsigned char*)ptr2;
    do {
      if (*p1++ != *p2++) {
        result = *--p1 - *--p2;
        break;
      }
    } while (--n != 0);
  }
  return result;
}
#include "s21_string.h"

char *s21_strerror(int errnum) {
  static char err_desc[100] = {'\0'};

  if (errnum >= 0 && errnum < ERR_NUM) {
    char *list[] = ERR_LIST;
    s21_sprintf(err_desc, "%s", list[errnum]);
  } else {
    s21_sprintf(err_desc, "%s %d", UNKNOWN_ERR, errnum);
  }

  return err_desc;
}
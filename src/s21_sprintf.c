#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  int flag = 0;
  SPEC_LIST spec_list = {.len = INIT_LEN, .cap = INIT_CAP};
  spec_list.list = malloc(spec_list.cap * sizeof(char *));
  parse_format(&spec_list, format, &flag);
  va_list arg;
  va_start(arg, format);
  char **output_list = malloc(spec_list.len * sizeof(char *));
  for (s21_size_t i = 0; i < spec_list.len; i++) {
    char spec = get_spec(spec_list.list[i]);
    prepare_output(spec_list.list[i], &output_list[i], arg, spec);
  }
  va_end(arg);

  fill_output_str(str, format, spec_list, output_list);
  if (!flag) {
    flag = s21_strlen(str);
  }
  free_lists(&spec_list, output_list);
  return flag;
}

void parse_format(SPEC_LIST *spec_list, const char *format, int *flag) {
  const char *ptr_cur = format;
  while ((ptr_cur < format + s21_strlen(format)) && !(*flag)) {
    if (*ptr_cur == '%') {
      ptr_cur++;
      char *ptr_spec = s21_strpbrk(ptr_cur, SPECS);
      if (ptr_spec) {
        s21_size_t spec_len = ptr_spec - ptr_cur + 1;
        char *spec_str = malloc(spec_len + 1);
        s21_strncpy(spec_str, ptr_cur, spec_len);
        spec_str[spec_len] = '\0';
        spec_list->list = append_list(spec_list->list, &spec_list->len,
                                      &spec_list->cap, spec_str);
        ptr_cur += spec_len;
      } else {
        *flag = -1;
      }
    } else {
      ptr_cur++;
    }
  }
}

char **append_list(char **list, s21_size_t *len, s21_size_t *cap, char *arg) {
  if (*len == *cap) {
    (*cap) *= 2;
    char **temp = realloc(list, sizeof(char *) * (*cap));
    list = temp;
  }

  list[*len] = arg;
  (*len)++;
  return list;
}

char get_spec(char *str) {
  char c = str[s21_strlen(str) - 1];
  return c;
}

void prepare_output(char *spec_str, char **output_str, va_list arg, char spec) {
  switch (spec) {
    case 'c':
      write_c(spec_str, output_str, arg);
      break;
    case 'd':
      write_d(spec_str, output_str, arg);
      break;
    case 'e':
      write_e(spec_str, output_str, arg);
      break;
    case 'E':
      write_e(spec_str, output_str, arg);
      break;
    case 'F':
    case 'f':
      write_f(spec_str, output_str, arg);
      break;
    case 'g':
    case 'G':
      write_g(spec_str, output_str, arg);
      break;
    case 'o':
      write_u(spec_str, output_str, arg, 8, 0);
      break;
    case 's':
      write_s(spec_str, output_str, arg);
      break;
    case 'u':
      write_u(spec_str, output_str, arg, 10, 0);
      break;
    case 'x':
      write_u(spec_str, output_str, arg, 16, 0);
      break;
    case 'X':
      write_u(spec_str, output_str, arg, 16, 1);
      break;
    case 'p':
      write_p(spec_str, output_str, arg);
      break;
    case '%':
      *output_str = (char *)calloc(2, sizeof(char));
      s21_strncat(*output_str, "%", 2);
      break;
    default:
      break;
  }
}

void write_c(char *spec_str, char **output_str, va_list arg) {
  int c = va_arg(arg, int);
  char *spec_ptr = spec_str;
  char flags_list[FLAGS_N + 1] = "e";
  check_flags(&spec_ptr, flags_list);
  int star_flag = 0, width = check_width(&spec_ptr, &star_flag);
  if (width == 0) {
    width = 1;
  }
  if (star_flag) {
    width = c;
    c = va_arg(arg, int);
  }

  char *value_ptr = (char *)calloc(2 + width, sizeof(char));

  if (s21_memchr(flags_list, '-', FLAGS_N)) {
    value_ptr[0] = c;
    for (int i = 1; i < width; i++) {
      s21_strncat(value_ptr, " ", 2);
    }
  } else {
    s21_memset(value_ptr, ' ', width - 1);
    value_ptr[width - 1] = c;
    value_ptr[width] = '\0';
  }
  *output_str = value_ptr;
}

void write_s(char *spec_str, char **output_str, va_list arg) {
  char *spec_ptr = spec_str;
  char flags_list[FLAGS_N + 1] = "e";
  check_flags(&spec_ptr, flags_list);
  int star_flag1 = 0, width = check_width(&spec_ptr, &star_flag1);
  int star_flag2 = 0, accuracy = check_accuracy(spec_ptr, &star_flag2);
  if (star_flag1) {
    width = va_arg(arg, int);
  }
  if (star_flag2) {
    accuracy = va_arg(arg, int);
  }
  char *s = va_arg(arg, char *);

  char *value_ptr = (char *)calloc(s21_strlen(s) + width + 5, sizeof(char));
  if (accuracy == -1) {
    s21_strncat(value_ptr, s, s21_strlen(s));
  } else {
    s21_strncat(value_ptr, s, MIN((s21_size_t)accuracy, s21_strlen(s)));
  }
  if ((s21_size_t)width > s21_strlen(value_ptr)) {
    int space = width - s21_strlen(value_ptr);
    if (s21_memchr(flags_list, '-', FLAGS_N)) {
      for (int i = 0; i < space; i++) {
        s21_strncat(value_ptr, " ", 2);
      }
    } else {
      make_offset(width, s21_strlen(value_ptr), value_ptr);
      s21_memset(value_ptr, ' ', space);
    }
  }
  *output_str = value_ptr;
}

void write_p(char *spec_str, char **output_str, va_list arg) {
  uint64_t p = va_arg(arg, uint64_t);
  char *spec_ptr = spec_str;
  char flags_list[FLAGS_N + 1] = "e";
  check_flags(&spec_ptr, flags_list);
  int star_flag1 = 0, width = check_width(&spec_ptr, &star_flag1);
  int star_flag2 = 0, accuracy = check_accuracy(spec_ptr, &star_flag2);
  if (star_flag1) {
    width = (int)p;
    p = va_arg(arg, uint64_t);
  }
  if (star_flag2) {
    accuracy = (int)p;
    p = va_arg(arg, uint64_t);
  }

  char *p_str;
  s21_utoa(p, &p_str, 16, 0);
  char *value_ptr =
      malloc(sizeof(char) * (s21_strlen(p_str) + width + accuracy + 5 + 2));
  value_ptr[0] = '\0';

  char sign = value_ptr[0];
  int length = s21_strlen(value_ptr) + s21_strlen(p_str) + 2;
  if (width == 0) {
    width = s21_ulen(p, 16) + 2;
  }
  if (!(accuracy == 0 && p == 0)) {
    s21_strncat(value_ptr, p_str, s21_strlen(p_str));
    width_implement_int(value_ptr, s21_ulen(p, 16), width - 2, accuracy,
                        flags_list);
  } else {
    width_implement_int(value_ptr, 0, width - 2, accuracy, flags_list);
  }
  post_processing(&value_ptr, flags_list, sign, length, width, accuracy + 2, 2,
                  0);
  *output_str = value_ptr;
  free(p_str);
}

void write_u(char *spec_str, char **output_str, va_list arg, int radix,
             int up_flag) {
  int l = check_length(spec_str);
  uint64_t x = get_arg_uint(arg, l);
  char *spec_ptr = spec_str;
  char flags_list[FLAGS_N + 1] = "e";
  check_flags(&spec_ptr, flags_list);
  int star_flag1 = 0, width = check_width(&spec_ptr, &star_flag1);
  int star_flag2 = 0, accuracy = check_accuracy(spec_ptr, &star_flag2);
  if (star_flag1) {
    width = (int)x;
    x = get_arg_uint(arg, l);
  }
  if (star_flag2) {
    accuracy = (int)x;
    x = get_arg_uint(arg, l);
  }
  int hash_flag = 0;
  if (s21_memchr(flags_list, '#', FLAGS_N) && x != 0) hash_flag += 1;
  int delta = make_delta(radix, hash_flag);
  char *x_str;
  s21_utoa(x, &x_str, radix, up_flag);
  char *value_ptr = malloc(sizeof(char) * (s21_strlen(x_str) + width +
                                           accuracy + 5 + delta));  // s21_
  value_ptr[0] = '\0';
  char sign = value_ptr[0];
  int length = s21_strlen(value_ptr) + s21_strlen(x_str) + delta;
  if (width == 0) {
    width = s21_ulen(x, 16) + delta;
  }
  if (!(accuracy == 0 && x == 0)) {
    s21_strncat(value_ptr, x_str, s21_strlen(x_str));  // s21_
    width_implement_int(value_ptr, s21_ulen(x, radix), width - delta, accuracy,
                        flags_list);
  } else {
    width_implement_int(value_ptr, 0, width - delta, accuracy, flags_list);
  }
  if (hash_flag) {
    post_processing(&value_ptr, flags_list, sign, length, width,
                    accuracy + delta, delta, up_flag);
  }

  *output_str = value_ptr;
  free(x_str);
}

void write_d(char *spec_str, char **output_str, va_list arg) {
  int l = check_length(spec_str);
  long long d = get_arg_int(arg, l);
  char *spec_ptr = spec_str;
  char flags_list[FLAGS_N + 1] = "e";
  check_flags(&spec_ptr, flags_list);
  int star_flag1 = 0, width = check_width(&spec_ptr, &star_flag1);
  int star_flag2 = 0, accuracy = check_accuracy(spec_ptr, &star_flag2);
  if (star_flag1) {
    width = (int)d;
    d = get_arg_int(arg, l);
  }
  if (star_flag2) {
    accuracy = (int)d;
    d = get_arg_int(arg, l);
  }

  char *d_str;
  s21_itoa(d, &d_str);
  char *value_ptr =
      malloc(sizeof(char) * (s21_strlen(d_str) + width + accuracy + 5));
  value_ptr[0] = '\0';

  if (s21_memchr(flags_list, '+', FLAGS_N) && d >= 0) {
    s21_strncat(value_ptr, "+", 2);
  } else if (s21_memchr(flags_list, ' ', FLAGS_N) && d >= 0) {
    s21_strncat(value_ptr, " ", 2);
  }

  if (!(accuracy == 0 && d == 0)) {
    s21_strncat(value_ptr, d_str, s21_strlen(d_str));
    width_implement_int(value_ptr, s21_ulen(llabs(d), 10), width, accuracy,
                        flags_list);
  } else {
    width_implement_int(value_ptr, 0, width, accuracy, flags_list);
  }
  *output_str = value_ptr;
  free(d_str);
}

void write_f(char *spec_str, char **output_str, va_list arg) {
  char *spec_ptr = spec_str;
  char flags_list[FLAGS_N + 1] = "e";
  check_flags(&spec_ptr, flags_list);
  int star_flag1 = 0, width = check_width(&spec_ptr, &star_flag1);
  int star_flag2 = 0, accuracy = check_accuracy(spec_ptr, &star_flag2);
  if (accuracy == -1) {
    accuracy = 6;
  }
  if (star_flag1) {
    width = va_arg(arg, long long);
  }
  if (star_flag2) {
    accuracy = va_arg(arg, long long);
  }
  int l = check_length_f(spec_str);
  long double num = get_arg_f(arg, l);
  char *num_str = S21_NULL;
  s21_gcvt(num, &num_str, accuracy);
  char *value_ptr =
      (char *)calloc(s21_strlen(num_str) + width + 2, sizeof(char));
  if (s21_memchr(flags_list, '+', FLAGS_N) && num >= 0) {
    s21_strncat(value_ptr, "+", 2);
  } else if (s21_memchr(flags_list, ' ', FLAGS_N) && num >= 0) {
    s21_strncat(value_ptr, " ", 2);
  }
  char sign = value_ptr[0];
  s21_strncat(value_ptr, num_str, s21_strlen(num_str));
  if ((s21_size_t)width > s21_strlen(value_ptr)) {
    if (!s21_memchr(flags_list, '-', FLAGS_N)) {
      int offset = make_offset(width, s21_strlen(value_ptr), value_ptr);
      if (!s21_memchr(flags_list, '0', FLAGS_N)) {
        s21_memset(value_ptr, ' ', offset);
      } else {
        if (sign == '-' || sign == '+' || sign == ' ') {
          offset++;
        }
        s21_memset(value_ptr, '0', offset);
        if (sign == '-' || sign == '+' || sign == ' ') {
          value_ptr[0] = sign;
        }
      }
    } else {
      for (int diff = width - s21_strlen(value_ptr); diff > 0; diff--) {
        s21_strncat(value_ptr, " ", 2);
      }
    }
  }
  *output_str = value_ptr;
  free(num_str);
}

void delete_trailing_zeros(char **str, int len, int is_e, int accuracy) {
  int digits_len = 0;
  int dot_len = 1, e_len = 0;
  if (is_e) {
    int i = len - 1;
    while ((*str)[i] != 'e' && (*str)[i] != 'E') {
      i--;
    }
    int j = i - 1;
    while ((*str)[j] == '0') {
      j--;
    }
    if ((*str)[j] == '.') {
      j--;
      dot_len = 0;
    }
    if (j != i - 1) {
      for (int k = j + 1, l = i; l < len; l++, k++) {
        (*str)[k] = (*str)[l];
      }
      for (int k = j + len - i + 1; k < len; k++) {
        (*str)[k] = '\0';
      }
    }
    digits_len = j + 1;
    e_len = len - i;
  } else {
    int j = len - 1;
    while ((*str)[j] == '0') {
      j--;
    }
    if ((*str)[j] == '.') {
      j--;
      dot_len = 0;
    }
    if (j != len - 1) {
      for (int k = j + 1; k < len; k++) {
        (*str)[k] = '\0';
      }
    }
    digits_len = j + 1;
  }
  char *new_res = NULL;
  int rest = 0;
  if (digits_len - dot_len > accuracy && is_e) {
    if ((*str)[accuracy + dot_len] >= '5') {
      rest = 1;
      for (int i = accuracy - 1 + dot_len; i >= 0; i--) {
        if (rest && (*str)[i] != '.') {
          if ((*str)[i] + rest > '9') {
            (*str)[i] = '0';
            rest = 1;
          } else {
            (*str)[i] += rest;
            rest = 0;
          }
        }
      }
    }
    new_res = (char *)calloc(len + 1, sizeof(char));
    if (rest) {
      new_res[0] = '1';
    }
    s21_strncpy(new_res + rest, *str, accuracy + dot_len - rest);
    int new_digit_len = s21_strlen(new_res);
    if (dot_len == 1 && new_res[new_digit_len - 1] == '.') {
      s21_strncpy(new_res + new_digit_len - 1, *str + digits_len, e_len);
    } else {
      s21_strncpy(new_res + new_digit_len, *str + digits_len, e_len);
    }
    char *tmp = *str;
    *str = new_res;
    free(tmp);
  } else if (digits_len - dot_len > accuracy && !is_e && (*str)[0] != '0') {
    new_res = (char *)calloc(len + 1, sizeof(char));
    s21_strncpy(new_res + rest, *str, accuracy + dot_len - rest);
    int new_digit_len = s21_strlen(new_res);
    if (dot_len == 1 && new_res[new_digit_len - 1] == '.') {
      new_res[new_digit_len - 1] = '\0';
    }
    char *tmp = *str;
    *str = new_res;
    free(tmp);
  }
}

void write_g(char *spec_str, char **output_str, va_list arg) {
  char *e_res = S21_NULL;
  char *f_res = S21_NULL;
  char *spec_ptr = spec_str;
  char flags_list[FLAGS_N + 1] = "e";
  check_flags(&spec_ptr, flags_list);
  int star_flag1 = 0, width = check_width(&spec_ptr, &star_flag1);
  int star_flag2 = 0, accuracy = check_accuracy(spec_ptr, &star_flag2);
  if (accuracy == -1) {
    accuracy = 6;
  } else if (accuracy == 0) {
    accuracy = 1;
  }
  if (star_flag1) {
    width = va_arg(arg, long long);
  }
  if (star_flag2) {
    accuracy = va_arg(arg, long long);
  }
  int l = check_length_f(spec_str);
  long double num = get_arg_f(arg, l);
  s21_gcvt_e(num, &e_res, accuracy,
             (spec_str[s21_strlen(spec_str) - 1] == 'G' ? 'E' : 'e'));
  s21_gcvt(num, &f_res, accuracy);
  int e_len = s21_strlen(e_res);
  int f_len = s21_strlen(f_res), len = 0;
  int power = 0, i = e_len - 1;
  for (int dec = 1; e_res[i] != '+' && e_res[i] != '-'; i--, dec *= 10) {
    power += (int)(e_res[i] - '0') * dec;
  }
  char *value_ptr =
      (char *)calloc((int)fmax(e_len, f_len) + width + 3, sizeof(char));
  char *res = S21_NULL;
  if ((power > 4 && e_res[i] == '-') ||
      (e_res[i] == '+' && power >= accuracy)) {
    delete_trailing_zeros(&e_res, e_len, 1, accuracy);
    res = e_res;
    len = e_len;
    free(f_res);
  } else {
    delete_trailing_zeros(&f_res, f_len, 0, accuracy);
    res = f_res;
    len = f_len;
    free(e_res);
  }
  if (s21_memchr(flags_list, '+', FLAGS_N) && num >= 0) {
    s21_strncat(value_ptr, "+", 2);
  } else if (s21_memchr(flags_list, ' ', FLAGS_N) && num >= 0) {
    s21_strncat(value_ptr, " ", 2);
  }
  char sign = value_ptr[0];
  s21_strncat(value_ptr, res, len);
  if ((s21_size_t)width > s21_strlen(value_ptr)) {
    if (!s21_memchr(flags_list, '-', FLAGS_N)) {
      int offset = make_offset(width, s21_strlen(value_ptr), value_ptr);
      if (!s21_memchr(flags_list, '0', FLAGS_N)) {
        s21_memset(value_ptr, ' ', offset);
      } else {
        if (sign == '-' || sign == '+' || sign == ' ') {
          offset++;
        }
        s21_memset(value_ptr, '0', offset);
        if (sign == '-' || sign == '+' || sign == ' ') {
          value_ptr[0] = sign;
        }
      }
    } else {
      for (int diff = width - s21_strlen(value_ptr); diff > 0; diff--) {
        s21_strncat(value_ptr, " ", 2);
      }
    }
  }
  *output_str = value_ptr;
  free(res);
}

void write_e(char *spec_str, char **output_str, va_list arg) {
  char *spec_ptr = spec_str;
  char flags_list[FLAGS_N + 1] = "e";
  check_flags(&spec_ptr, flags_list);
  int star_flag1 = 0, width = check_width(&spec_ptr, &star_flag1);
  int star_flag2 = 0, accuracy = check_accuracy(spec_ptr, &star_flag2);
  if (accuracy == -1) {
    accuracy = 6;
  }
  if (star_flag1) {
    width = va_arg(arg, long long);
  }
  if (star_flag2) {
    accuracy = va_arg(arg, long long);
  }
  int l = check_length_f(spec_str);
  long double num = get_arg_f(arg, l);
  char *num_str = S21_NULL;
  s21_gcvt_e(num, &num_str, accuracy, spec_str[s21_strlen(spec_str) - 1]);
  char *value_ptr =
      (char *)calloc(s21_strlen(num_str) + width + 2, sizeof(char));

  if (s21_memchr(flags_list, '+', FLAGS_N) && num >= 0) {  // s21_
    s21_strncat(value_ptr, "+", 2);
  } else if (s21_memchr(flags_list, ' ', FLAGS_N) && num >= 0) {
    s21_strncat(value_ptr, " ", 2);
  }
  char sign = value_ptr[0];
  s21_strncat(value_ptr, num_str, s21_strlen(num_str));
  if ((s21_size_t)width > s21_strlen(value_ptr)) {
    if (!s21_memchr(flags_list, '-', FLAGS_N)) {
      int offset = make_offset(width, s21_strlen(value_ptr), value_ptr);
      if (!s21_memchr(flags_list, '0', FLAGS_N)) {
        s21_memset(value_ptr, ' ', offset);
      } else {
        if (sign == '-' || sign == '+' || sign == ' ') {
          offset++;
        }
        s21_memset(value_ptr, '0', offset);
        if (sign == '-' || sign == '+' || sign == ' ') {
          value_ptr[0] = sign;
        }
      }
    } else {
      for (int diff = width - s21_strlen(value_ptr); diff > 0; diff--) {
        s21_strncat(value_ptr, " ", 2);
      }
    }
  }
  *output_str = value_ptr;
  free(num_str);
}

int check_width(char **spec_ptr, int *star_flag) {
  int res = 0;
  char *width_ptr = s21_strpbrk(*spec_ptr, WIDTH_SPECS);
  s21_size_t width_len = width_ptr - *spec_ptr;
  if (width_len) {
    if (**spec_ptr == '*') {
      *star_flag = 1;
    } else {
      res = str_to_int(*spec_ptr, width_len);
    }
  }
  *spec_ptr = width_ptr;
  return res;
}

int str_to_int(char *ptr, s21_size_t len) {
  int res = 0;  // -1
  for (int i = 0; ptr + i < ptr + len; i++) {
    res += (*(ptr + i) - 48) * (int)(pow(10, len - i - 1) + 1e-9);
  }
  return res;
}

int check_length(char *spec_str) {
  int res = 0;
  if (s21_strlen(spec_str) > 1 && (spec_str[s21_strlen(spec_str) - 2] == 'l' ||
                                   spec_str[s21_strlen(spec_str) - 2] == 'L')) {
    if (s21_strlen(spec_str) > 2 && spec_str[s21_strlen(spec_str) - 3] == 'l') {
      res = 2;
    } else {
      res = 1;
    }
  }
  if (s21_strlen(spec_str) > 1 && (spec_str[s21_strlen(spec_str) - 2] == 'h')) {
    res = -1;
  }
  // res = -1 - short; res = 1 - Long/long; res = 2 - long long
  return res;
}

int check_length_f(char *spec_str) {
  int res = 0;
  if (s21_strlen(spec_str) > 1 && (spec_str[s21_strlen(spec_str) - 2] == 'l')) {
    res = 1;
  } else if (s21_strlen(spec_str) > 1 &&
             (spec_str[s21_strlen(spec_str) - 2] == 'L')) {
    res = 2;
  }
  return res;
}

void check_flags(char **spec_ptr, char *flags) {
  char *flags_ptr = s21_strpbrk(*spec_ptr, FLAGS_SPECS);
  int k = 0;

  for (int i = 0; *spec_ptr + i < flags_ptr; i++) {
    char value = *(*spec_ptr + i);
    if (s21_memchr(FLAGS, value, FLAGS_N) &&
        !s21_memchr(flags, value, FLAGS_N + 1)) {
      flags[k] = value;
      k++;
    }
  }
  *spec_ptr = flags_ptr;
}

int check_accuracy(char *spec_ptr, int *star_flag) {
  int res = -1;
  if (spec_ptr[0] == '.') {
    spec_ptr++;
    res = 0;
  }
  char *accuracy_ptr = s21_strpbrk(spec_ptr, ACCURACY_SPECS);
  s21_size_t accuracy_len = accuracy_ptr - spec_ptr;
  if (accuracy_len) {
    if (*spec_ptr == '*') {
      *star_flag = 1;
    } else {
      res = str_to_int(spec_ptr, accuracy_len);
    }
  }
  return res;
}

void width_implement_int(char *str, int count_digits, int width, int accuracy,
                         char *flags) {
  char sign = str[0];
  if (accuracy > count_digits) {
    int offset = make_offset(accuracy, count_digits, str);
    if (sign == '-' || sign == '+' || sign == ' ') {
      offset++;
    }
    s21_memset(str, '0', offset);
    if (sign == '-' || sign == '+' || sign == ' ') {
      str[0] = sign;
    }
  }

  if ((s21_size_t)width > s21_strlen(str)) {
    if (!s21_memchr(flags, '-', FLAGS_N)) {
      int offset = make_offset(width, s21_strlen(str), str);
      if (!s21_memchr(flags, '0', FLAGS_N)) {
        s21_memset(str, ' ', offset);
      } else {
        if (accuracy != -1) {
          s21_memset(str, ' ', offset);
        } else {
          if (sign == '-' || sign == '+' || sign == ' ') {
            offset++;
          }
          s21_memset(str, '0', offset);
          if (sign == '-' || sign == '+' || sign == ' ') {
            str[0] = sign;
          }
        }
      }
    } else {
      int diff = width - s21_strlen(str);
      for (; diff > 0; diff--) {
        s21_strncat(str, " ", 2);
      }
    }
  }
}

int make_offset(int n1, int n2, char *str) {
  int offset = n1 - n2;
  for (int i = 0; i < offset; i++) {
    for (int j = s21_strlen(str); j >= i; j--) {
      str[j + 1] = str[j];
    }
  }
  return offset;
}

uint64_t get_arg_uint(va_list arg, int l) {
  uint64_t d;
  if (l == 0 || l == -1) {
    d = va_arg(arg, unsigned int);
  } else if (l == 1) {
    d = va_arg(arg, unsigned long);
  } else if (l == 2) {
    d = va_arg(arg, unsigned long long);
  }
  return d;
}

long long get_arg_int(va_list arg, int l) {
  long long d;
  if (l == 0 || l == -1) {
    d = va_arg(arg, int);
  } else if (l == 1) {
    d = va_arg(arg, long);
  } else if (l == 2) {
    d = va_arg(arg, long long);
  }
  return d;
}

void post_processing(char **value_ptr, char *flags_list, char sign, int length,
                     int width, int accuracy, int delta, int up_flag) {
  make_offset(delta, 0, *value_ptr);
  char hash_symb = 'x';
  if (up_flag) {
    hash_symb = 'X';
  }
  int i = 0;
  if (!(s21_memchr(flags_list, '-', FLAGS_N))) {
    if (s21_memchr(flags_list, '0', FLAGS_N)) {
      if (sign == '+' || sign == ' ') {
        i++;
      }
      (*value_ptr)[i] = '0';
      if (delta == 2) (*value_ptr)[i + 1] = hash_symb;
    } else {
      if (sign == '+' || sign == ' ') {
        (*value_ptr)[width - MAX(length, accuracy)] = '+';
        i++;
      }
      if (width > MAX(length, accuracy)) {
        (*value_ptr)[width - MAX(length, accuracy) + i] = '0';
        if (delta == 2)
          (*value_ptr)[width - MAX(length, accuracy) + i + 1] = hash_symb;
      } else {
        (*value_ptr)[i] = '0';
        if (delta == 2) (*value_ptr)[i + 1] = hash_symb;
      }
    }
  } else {
    if (sign == '+' || sign == ' ') {
      i++;
    }
    (*value_ptr)[i] = '0';
    if (delta == 2) (*value_ptr)[i + 1] = hash_symb;
  }
}

int s21_ulen(uint64_t num, int radix) {
  int len = 0;
  if (num == 0) {
    len = 1;
  }
  while (num > 0) {
    len += 1;
    num /= radix;
  }
  return len;
}

void s21_itoa(long long num, char **result) {
  int delta = 0;
  if (num < 0) {
    num = num * (-1);
    delta += 1;
  }
  int len = s21_ulen(num, 10);
  *result = calloc(len + delta + 1, sizeof(char));
  (*result)[len + delta] = '\0';
  if (delta == 1 && num != 0) {
    (*result)[0] = '-';
  }
  for (int i = len + delta - 1; i >= delta; i--) {
    int digit = num % 10;
    num /= 10;
    (*result)[i] = '0' + digit;
  }
}

void s21_gcvt(long double num, char **result, int precision) {
  int delta = 0;
  if (num < 0) {
    num = num * (-1.0);
    delta += 1;
  }
  long integer_part = num;
  int integer_len = s21_ulen(integer_part, 10);
  long double plug;
  long fractional_part =
      (lroundl)(floorl(modfl(num, &plug) * pow(10, precision + 1)) / 10);
  int rest = 0;
  if (s21_ulen(fractional_part, 10) > precision && precision) {
    fractional_part--;
    rest = 1;
  } else if (!precision && fractional_part != 0) {
    rest = 1;
  }
  int fractional_len = fmax(s21_ulen(fractional_part, 10), precision);
  int digit;
  *result =
      (char *)calloc(integer_len + fractional_len + delta + 3, sizeof(char));
  (*result)[integer_len + fractional_len + delta + 1] = '\0';
  if (precision) {
    (*result)[integer_len + delta] = '.';
    for (int i = integer_len + fractional_len + delta; i > integer_len + delta;
         i--) {
      digit = fractional_part % 10;
      fractional_part /= 10;
      if (rest) {
        int temp = (digit + rest) % 10;
        rest = (digit + rest) / 10;
        digit = temp;
      }
      (*result)[i] = '0' + digit;
    }
  }
  if (delta == 1) {
    (*result)[0] = '-';
  }
  for (int i = integer_len + delta - 1; i >= delta; i--) {
    digit = integer_part % 10;
    integer_part /= 10;
    if (rest) {
      int temp = (digit + rest) % 10;
      rest = (digit + rest) / 10;
      digit = temp;
    }
    (*result)[i] = '0' + digit;
  }
  if (rest) {
    int len = s21_strlen(*result);
    char *new_res = (char *)calloc(len + 2, sizeof(char));
    new_res[0] = '1';
    s21_strncpy(new_res + 1, *result, len);
    char *tmp = *result;
    *result = new_res;
    free(tmp);
  }
}

void s21_utoa(uint64_t num, char **result, int radix, int up_flag) {
  char alphabet[16] = "0123456789abcdef";
  if (up_flag) {
    alphabet[10] = 'A';
    alphabet[11] = 'B';
    alphabet[12] = 'C';
    alphabet[13] = 'D';
    alphabet[14] = 'E';
    alphabet[15] = 'F';
  }
  int len = s21_ulen(num, radix);
  *result = calloc(len + 1, sizeof(char));
  (*result)[len] = '\0';
  for (int i = len - 1; i >= 0; i--) {
    int digit = num % radix;
    num /= radix;
    (*result)[i] = alphabet[digit];
  }
}

void s21_gcvt_e(long double num, char **res, int precision, char spec) {
  long double copy = num;
  if (copy < 0) {
    copy *= (-1);
  }
  long power = 0;
  long long integer_part = (long long)copy;
  long long int_len = s21_ulen(integer_part, 10);
  if (integer_part == 0 && num != 0.0) {
    do {
      copy *= 10;
      power--;
    } while ((long long)copy == 0);
  } else if (integer_part != 0) {
    power = int_len - 1;
  }

  s21_gcvt(num / pow(10, power), res, precision);
  int power_len = s21_ulen(labs(power), 10);
  long digits_len = s21_strlen(*res);
  char *buf = (char *)calloc(digits_len + 1, sizeof(char));
  s21_strncpy(buf, *res, digits_len);
  char *tmp = *res;
  char *res1 = (char *)calloc(digits_len + power_len + 5, sizeof(char));
  *res = res1;
  free(tmp);
  s21_strncpy(*res, buf, digits_len);
  free(buf);
  (*res)[digits_len] = spec;
  (*res)[digits_len + 1] = power < 0 ? '-' : '+';
  power = power < 0 ? -power : power;
  if (power < 10) {
    (*res)[digits_len + 2] = '0';
    (*res)[digits_len + 3] = '0' + power;
  } else {
    for (int i = digits_len + 2 + power_len - 1; i >= digits_len + 2; i--) {
      (*res)[i] = '0' + power % 10;
      power /= 10;
    }
  }
}

int make_delta(int radix, int hash_flag) {
  int delta = 0;
  if (hash_flag) {
    delta += 1;
    if (radix == 16) {
      delta += 1;
    }
  }
  return delta;
}

long double get_arg_f(va_list arg, int l) {
  long double d;
  if (l == 0) {
    d = va_arg(arg, double);
  } else if (l == 1) {
    d = va_arg(arg, double);
  } else if (l == 2) {
    d = va_arg(arg, long double);
  }
  return d;
}

void fill_output_str(char *str, const char *format, SPEC_LIST spec_list,
                     char **output_list) {
  str[0] = '\0';
  int i = 0;
  const char *format_ptr = format;
  char *str_ptr = str;
  while (*format_ptr) {
    if (*format_ptr == '%') {
      s21_strncat(str, output_list[i], s21_strlen(output_list[i]));
      format_ptr += s21_strlen(spec_list.list[i]) + 1;
      str_ptr += s21_strlen(output_list[i]);
      i++;
    } else {
      *str_ptr = *format_ptr;
      *(++str_ptr) = '\0';
      format_ptr++;
    }
  }
}

void free_lists(SPEC_LIST *spec_list, char **output_list) {
  for (s21_size_t i = 0; i < spec_list->len; i++) {
    free(spec_list->list[i]);
    free(output_list[i]);
  }

  free(spec_list->list);
  free(output_list);
}
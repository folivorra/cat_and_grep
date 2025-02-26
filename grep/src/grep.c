#include "../include/grep.h"

int apply_flags(flags f) {
  int flag = 0, err = 0, err_f = 0;
  if (f.paths_c > 1 && f.h != 1) flag = 1;
  if (f.f == 1) err_f = flag_f(&f);
  if (!err_f) {
    for (int i = 0; i < f.paths_c; i++) {
      if ((err = flags_to_sort(f, i)) == 1) {
        flags_to_print(f, flag, i);
      } else if (err == -1) {
        printf("Regular expression didn`t compiled\n");
      } else if (f.s != 1) {
        printf("%s doesn`t exist\n", f.paths[i]);
      }
      remove("tmp");
    }
  }
  return err;
}

int flag_o(flags f, FILE* fr, FILE* fw) {
  char str[MAX_LEN];
  int err = 1;
  while (fgets(str, MAX_LEN, fr) != NULL) {
    regex_t regt;
    regmatch_t match;
    for (int i = 0; i < f.tmplt_c; i++) {
      char str_dup[MAX_LEN];
      strcpy(str_dup, str);
      if (f.i) {
        strlwr(f.tmplt_m[i]);
        strlwr(str_dup);
      }
      int val;
      char* cur = str_dup;
      if ((err = regcomp(&regt, f.tmplt_m[i], 0))) {
        err = -1;
        break;
      } else {
        err = 1;
      }
      while ((val = regexec(&regt, cur, 1, &match, 0)) == 0) {
        fprintf(fw, "%.*s\n", (int)(match.rm_eo - match.rm_so),
                str + (cur - str_dup) + match.rm_so);
        cur += match.rm_eo;
      }
      regfree(&regt);
    }
  }
  return err;
}

int flag_i(flags f, FILE* fr, FILE* fw) {
  char str[MAX_LEN];
  int res = 0;
  while (fgets(str, MAX_LEN, fr) != NULL) {
    char tmp_str[MAX_LEN];
    strcpy(tmp_str, str);
    strlwr(tmp_str);
    if ((res = to_find_patt(f, tmp_str)) == 1) {
      fprintf(fw, "%s", str);
    } else if (res == -1) {
      break;
    } else {
      res = 1;
    }
  }
  return res;
}

int flag_v(flags f, FILE* fr, FILE* fw) {
  char str[MAX_LEN];
  int res = 0;
  while (fgets(str, MAX_LEN, fr) != NULL) {
    if ((res = to_find_patt(f, str)) == 0) {
      fprintf(fw, "%s", str);
      res = 1;
    } else if (res == -1) {
      break;
    }
  }
  return res;
}

int flags_iv(flags f, FILE* fr, FILE* fw) {
  char str[MAX_LEN];
  int res = 0;
  while (fgets(str, MAX_LEN, fr) != NULL) {
    char tmp_str[MAX_LEN];
    strcpy(tmp_str, str);
    strlwr(tmp_str);
    if ((res = to_find_patt(f, tmp_str)) == 0) {
      fprintf(fw, "%s", str);
      res = 1;
    } else if (res == -1) {
      break;
    }
  }
  return res;
}

void flag_c(int flag, FILE* fr, const char* path) {
  char str[MAX_LEN];
  int counter = 0;
  while (fgets(str, MAX_LEN, fr) != NULL) {
    counter++;
  }
  if (flag)
    printf("%s:%d", path, counter);
  else
    printf("%d", counter);
  printf("\n");
}

void flag_l(FILE* fr, const char* path) {
  char str[MAX_LEN];
  if (fgets(str, MAX_LEN, fr) != NULL) printf("%s\n", path);
}

void flag_n(int flag, FILE* fr, const char* path) {
  char str_counter[MAX_LEN];
  FILE* fr_counter = fopen(path, "r");
  int counter = 0;
  char str[MAX_LEN];
  fgets(str, MAX_LEN, fr);
  while (fgets(str_counter, MAX_LEN, fr_counter) != NULL) {
    counter++;
    if (!strncmp(str, str_counter, strlen(str_counter))) {
      if (flag)
        printf("%s:%d:%s", path, counter, str_counter);
      else
        printf("%d:%s", counter, str_counter);
      fgets(str, MAX_LEN, fr);
    }
  }
  if (str[strlen(str) - 1] != '\n' && strlen(str) > 1) printf("\n");
  fclose(fr_counter);
}

int no_flag(flags f, FILE* fr, FILE* fw) {
  char str[MAX_LEN];
  int res = 0;
  while (fgets(str, MAX_LEN, fr) != NULL) {
    if ((res = to_find_patt(f, str)) == 1) {
      fprintf(fw, "%s", str);
    } else if (res == -1) {
      break;
    } else {
      res = 1;
    }
  }
  return res;
}

char* strlwr(char* str) {
  char* ptr = str;
  while (*ptr) {
    *ptr = tolower(*ptr);
    ptr++;
  }
  return str;
}

int to_find_patt(flags f, char* buff) {
  regex_t regt;
  int flag = 0;
  for (int i = 0; i < f.tmplt_c; i++) {
    int val;
    if (f.i) strlwr(f.tmplt_m[i]);
    if (regcomp(&regt, f.tmplt_m[i], 0)) {
      flag = -1;
      break;
    }
    val = regexec(&regt, buff, 0, NULL, 0);
    regfree(&regt);
    if (val == 0) flag = 1;
  }
  return flag;
}

int flags_to_sort(flags f, int ind) {
  int err = 0;
  FILE* fr = fopen(f.paths[ind], "r");
  FILE* fw = fopen("tmp", "a");
  if (fr == NULL) {
    err = 2;
  } else {
    if (f.i && f.v) {
      err = flags_iv(f, fr, fw);
    } else if ((f.i && f.o) || (!f.i && f.o)) {
      err = flag_o(f, fr, fw);
    } else if (f.i) {
      err = flag_i(f, fr, fw);
    } else if (f.v) {
      err = flag_v(f, fr, fw);
    } else
      err = no_flag(f, fr, fw);
    fclose(fr);
  }
  fclose(fw);
  return err;
}

void flags_to_print(flags f, int flag, int ind) {
  FILE* fr = fopen("tmp", "r");
  if (f.l) {
    flag_l(fr, f.paths[ind]);
  } else if (f.c) {
    flag_c(flag, fr, f.paths[ind]);
  } else if (f.n) {
    flag_n(flag, fr, f.paths[ind]);
  } else {
    char str[MAX_LEN];
    while (fgets(str, MAX_LEN, fr) != NULL) {
      if (flag)
        printf("%s:%s", f.paths[ind], str);
      else
        printf("%s", str);
    }
    if (str[strlen(str) - 1] != '\n' && strlen(str) > 1) printf("\n");
  }
  fclose(fr);
  remove("tmp");
}

int flag_f(flags* f) {
  int err = 0;
  FILE* fr = fopen(f->f_path, "r");
  if (fr == NULL) {
    printf("%s doesn`t exist\n", f->f_path);
    err = 1;
  } else {
    char tmpl[MAX_STR];
    while (fgets(tmpl, MAX_STR, fr) != NULL) {
      if (tmpl[strlen(tmpl) - 1] == '\n') tmpl[strlen(tmpl) - 1] = '\0';
      strcpy(f->tmplt_m[f->tmplt_c++], tmpl);
    }
    fclose(fr);
  }
  return err;
}
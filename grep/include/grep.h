#ifndef GREP
#define GREP

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 4096
#define MAX_STR 256

typedef struct flags {
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
  char f_path[MAX_STR];
  int f;
  char tmplt_m[100][MAX_STR];
  int tmplt_c;
  char paths[50][MAX_STR];
  int paths_c;
} flags;

int apply_flags(flags f);
int flags_iv(flags f, FILE* fr, FILE* fw);
int flag_i(flags f, FILE* fr, FILE* fw);
int flag_v(flags f, FILE* fr, FILE* fw);
void flag_c(int flag, FILE* fr, const char* path);
void flag_l(FILE* fr, const char* path);
void flag_n(int flag, FILE* fr, const char* path);
int flag_f(flags* f);
int flag_o(flags f, FILE* fr, FILE* fw);
int no_flag(flags f, FILE* fr, FILE* fw);
char* strlwr(char* str);
int to_find_patt(flags f, char* buff);
int to_find_patt_o(flags* f, char* buff);
int flags_to_sort(flags f, int ind);
void flags_to_print(flags f, int flag, int ind);

#endif
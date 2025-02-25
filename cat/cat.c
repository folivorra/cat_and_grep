#include "cat.h"

void simple_write(FILE* fr, FILE* fout) {
  char c;
  while ((c = fgetc(fr)) != EOF) {
    fputc(c, fout);
  }
}

void with_all_columns(FILE* fr, FILE* fout) {
  char c;
  int i = 1, flag = 1;
  while ((c = fgetc(fr)) != EOF) {
    if (flag) {
      fprintf(fout, "%6d\t", i++);
      flag = 0;
    }
    fputc(c, fout);
    if (c == '\n') {
      flag = 1;
    }
  }
}

void without_all_columns(FILE* fr, FILE* fout) {
  char c;
  int i = 1, flag = 1;
  while ((c = fgetc(fr)) != EOF) {
    if (flag == 1 && c != '\n') {
      fprintf(fout, "%6d\t", i++);
      flag = 0;
    }
    fputc(c, fout);
    if (c == '\n') {
      flag = 1;
    }
  }
}

void squeze(FILE* fr, FILE* fout) {
  char c;
  int flag = 1;
  while ((c = fgetc(fr)) != EOF) {
    if (c == '\n')
      flag++;
    else
      flag = 0;

    if (flag < 3) fputc(c, fout);
  }
}

void only_dollar(FILE* fr, FILE* fout) {
  char c;
  while ((c = fgetc(fr)) != EOF) {
    if (c == '\n')
      fputs("$\n", fout);
    else
      fputc(c, fout);
  }
}

void only_I(FILE* fr, FILE* fout) {
  char c;
  while ((c = fgetc(fr)) != EOF) {
    if (c == '\t')
      fputs("^I", fout);
    else
      fputc(c, fout);
  }
}

void without_dollar_I(FILE* fr, FILE* fout) {
  long buffer;
  while ((buffer = fgetc(fr)) != EOF) {
    char s[5] = "";
    if (buffer < 32 && buffer != 9 && buffer != 10) {
      strcat(s, "^");
      buffer += 64;
    } else if (buffer > 127 && buffer < 160)
      strcat(s, "M-^");
    else if (buffer >= 160)
      strcat(s, "M-");
    if (buffer > 127) {
      buffer -= 128;
      if (buffer < 32 && buffer != 9 && buffer != 10) buffer += 64;
    }
    if (buffer == 127)
      fprintf(fout, "^?");
    else
      fprintf(fout, "%s%c", s, (char)buffer);
  }
}

void cpy_out_outr() {
  FILE* fr = fopen("out", "rb");
  FILE* fw = fopen("outr", "wb");
  int c;
  while ((c = fgetc(fr)) != EOF) {
    fputc(c, fw);
  }
  fclose(fr);
  fclose(fw);
}
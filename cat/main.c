#include "cat.h"

typedef struct bool {
  int b;
  int n;
  int s;
  int be;
  int bt;
  int v;
}
bool;

void flags(const char* argv[], int argc);
int files(const char* argv[], int argc, FILE** tmp);
void processing_file(bool f, int count);
void output();

int main(int argc, const char* argv[]) {
  FILE* file;
  if (files(argv, argc, &file)) {
    printf("File doesn`t exist\n");
  } else {
    rewind(file);
    fseek(file, 0, SEEK_END);
    long pos = ftell(file);
    if (pos == 0) remove("tmp");
    fclose(file);
    flags(argv, argc);
  }
  remove("tmp");
  return 0;
}

void flags(const char* argv[], int argc) {
  bool f = {0};
  int c = 0;
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], N) || !strcmp(argv[i], LN)) {
      f.n = 1;
      c = 1;
    } else if (!strcmp(argv[i], B) || !strcmp(argv[i], LB)) {
      f.b = 1;
      c = 1;
    } else if (!strcmp(argv[i], S) || !strcmp(argv[i], LS)) {
      f.s = 1;
      c = 1;
    } else if (!strcmp(argv[i], BE)) {
      f.be = 1;
      c = 1;
    } else if (!strcmp(argv[i], BT)) {
      f.bt = 1;
      c = 1;
    } else if (!strcmp(argv[i], V)) {
      f.v = 1;
      c = 1;
    } else if (!strcmp(argv[i], E)) {
      f.be = 1;
      f.v = 1;
      c = 1;
    } else if (!strcmp(argv[i], T)) {
      f.bt = 1;
      f.v = 1;
      c = 1;
    }
  }
  processing_file(f, c);
  remove("outr");
  output();
}

int files(const char* argv[], int argc, FILE** tmp) {
  *tmp = fopen("tmp", "a+b");
  int flag = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], N) && strcmp(argv[i], B) && strcmp(argv[i], S) &&
        strcmp(argv[i], BE) && strcmp(argv[i], BT) && strcmp(argv[i], V) &&
        strcmp(argv[i], E) && strcmp(argv[i], T) && strcmp(argv[i], LB) &&
        strcmp(argv[i], LN) && strcmp(argv[i], LS)) {
      FILE* fr = fopen(argv[i], "rb");
      if (fr == NULL) {
        flag = 1;
        break;
      }
      char c;
      while ((c = fgetc(fr)) != EOF) {
        fputc(c, *tmp);
      }
      fclose(fr);
    }
  }
  return flag;
}

void output() {
  FILE* fout = fopen("out", "rb");
  if (fout == NULL) fout = fopen("tmp", "rb");
  if (fout == NULL) fout = stdin;
  char c;
  while ((c = fgetc(fout)) != EOF) {
    fputc(c, stdout);
  }
  fclose(fout);
  remove("out");
}

void processing_file(bool f, int count) {
  FILE* fr = fopen("tmp", "rb");
  FILE* fout;
  if (fr == NULL && count == 0)
    simple_write(stdin, stdout);
  else {
    if (fr == NULL) fr = stdin;
    while (f.n != 0 || f.bt != 0 || f.s != 0 || f.b != 0 || f.v != 0 ||
           f.be != 0) {
      fout = fopen("out", "wb");
      if (f.bt == 1) {
        only_I(fr, fout);
        f.bt = 0;
      } else if (f.s == 1) {
        squeze(fr, fout);
        f.s = 0;
      } else if (f.n == 1 && f.b == 0) {
        with_all_columns(fr, fout);
        f.n = 0;
      } else if (f.n == 1 && f.b == 1) {
        without_all_columns(fr, fout);
        f.n = 0;
        f.b = 0;
      } else if (f.n == 0 && f.b == 1) {
        without_all_columns(fr, fout);
        f.b = 0;
      } else if (f.be == 1) {
        only_dollar(fr, fout);
        f.be = 0;
      } else if (f.v == 1) {
        without_dollar_I(fr, fout);
        f.v = 0;
      }
      fclose(fout);
      fclose(fr);
      cpy_out_outr();
      fr = fopen("outr", "rb");
    }
    if (count == 0) {
      fout = fopen("out", "wb");
      simple_write(fr, fout);
      fclose(fout);
    }
    fclose(fr);
  }
}
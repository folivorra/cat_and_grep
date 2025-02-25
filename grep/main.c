#include "grep.h"

int parser(int argc, char* argv[], flags* f);

int main(int argc, char* argv[]) {
  flags f = {0};
  if (parser(argc, argv, &f))
    printf("Error flags\n");
  else if (f.paths_c == 0 && f.s == 0)
    printf("Error files\n");
  else
    apply_flags(f);
  return 0;
}

int parser(int argc, char* argv[], flags* f) {
  int rez, err = 0;
  opterr = 0;
  while ((rez = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (rez) {
      case 'e':
        snprintf(f->tmplt_m[f->tmplt_c++], MAX_STR, "%s", optarg);
        break;
      case 'i':
        f->i = 1;
        break;
      case 'v':
        f->v = 1;
        break;
      case 'c':
        f->c = 1;
        break;
      case 'l':
        f->l = 1;
        break;
      case 'n':
        f->n = 1;
        break;
      case 'h':
        f->h = 1;
        break;
      case 's':
        f->s = 1;
        break;
      case 'f':
        f->f = 1;
        snprintf(f->f_path, MAX_STR, "%s", optarg);
        break;
      case 'o':
        f->o = 1;
        break;
      case '?':
        err = 1;
        break;
    }
  }
  if (f->tmplt_c == 0 && f->f == 0)
    snprintf(f->tmplt_m[f->tmplt_c++], MAX_STR, "%s", argv[optind++]);
  while (optind < argc) {
    snprintf(f->paths[f->paths_c++], MAX_STR, "%s", argv[optind++]);
  }
  return err;
}
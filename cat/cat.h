#ifndef CAT
#define CAT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N "-n"
#define B "-b"
#define T "-t"
#define E "-e"
#define S "-s"
#define V "-v"
#define BE "-E"
#define BT "-T"
#define LB "--number-nonblank"
#define LN "--number"
#define LS "--squeeze-blank"

void simple_write(FILE* fr, FILE* fout);
void with_all_columns(FILE* fr, FILE* fout);
void without_all_columns(FILE* fr, FILE* fout);
void squeze(FILE* fr, FILE* fout);
void only_dollar(FILE* fr, FILE* fout);
void only_I(FILE* fr, FILE* fout);
void without_dollar_I(FILE* fr, FILE* fout);
void cpy_out_outr();

#endif
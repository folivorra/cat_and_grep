GCC=gcc -Wall -Werror -Wextra -std=c11
CLANG=clang-format -i *.c *.h

all: rebuild

s21_cat: main.c cat.c
	$(GCC) $^ -g -pedantic -o s21_cat

clean:
	rm -f *s21_cat

rebuild: clean s21_cat
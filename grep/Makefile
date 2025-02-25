GCC=gcc -Wall -Werror -Wextra -std=c11
CLANG=clang-format -i *.c *.h

all: rebuild

s21_grep: main.c grep.c
	$(GCC) $^ -g -pedantic -o s21_grep 

clean:
	rm -f *s21_grep

rebuild: clean s21_grep
GCC=gcc -Wall -Werror -Wextra -std=c11
SRCS=src/*.c
EXENAME=build/s21_cat

all: $(EXENAME)

$(EXENAME): $(SRCS)
	mkdir -p build
	$(GCC) $^ -g -pedantic -o $(EXENAME)

clean:
	rm -rf build

rebuild: clean $(EXENAME)
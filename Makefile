CFLAGS=-Wall -Wextra -Werror -g

.PHONY: all test libftprintf.a

all: test

test: tests_runner.c libftprintf.a
	cc $(CFLAGS) -o test tests_runner.c -L.. -lftprintf

libftprintf.a:
	make -C .. all

clean:
	make -C .. fclean

fclean: clean
	rm -f test

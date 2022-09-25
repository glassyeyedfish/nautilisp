nautilisp:
	cc -ansi -pedantic -Werror -Wall -Wextra \
	src/*.c src/mpc/mpc.c \
	-ledit -lm \
	-o build/nautilisp
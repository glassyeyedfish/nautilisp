nautilisp:
	cc -ansi -pedantic -Werror -Wall \
	nautilisp.c mpc/mpc.c \
	-ledit -lm \
	-o build/nautilisp
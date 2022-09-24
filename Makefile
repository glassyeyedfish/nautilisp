nautilisp: nautilisp.c
	cc -std=c99 -Wall \
	nautilisp.c mpc.c \
	-ledit -lm \
	-o nautilisp
#ifndef LVAL_H
#define LVAL_H

typedef struct {
        int type;
        long num;
        char* err;
        char* sym;
        int count;
        struct lval** cell;
} lval;

enum {
        LVAL_NUM,
        LVAL_ERR,
        LVAL_SYM,
        LVAL_SEXPR
};

enum {
        LERR_DIV_ZERO,
        LERR_BAD_OP,
        LERR_BAD_NUM
};

lval* lval_num(long x);
lval* lval_err(char* m);
lval* lval_sym(char* s);
lval* lval_sexpr(void);
void lval_print(lval v);
void lval_println(lval v);

#endif
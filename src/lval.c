#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lval.h"

lval*
lval_num(long x) {
        lval* v = malloc(sizeof(lval));
        v->type = LVAL_NUM;
        v->num = x;
        return v;
}

lval*
lval_err(char* m) {
        lval* v = malloc(sizeof(lval));
        v->type = LVAL_ERR;
        v->err = malloc(strlen(m) + 1);
        strcpy(v->err, m);
        return v;
}

lval*
lval_sym(char* s) {
        lval* v = malloc(sizeof(lval));
        v->type = LVAL_SYM;
        v->sym = malloc(strlen(s) + 1);
        strcpy(v->sym, s);
        return v;
}

lval*
lval_sexpr(void) {
        lval* v = malloc(sizeof(lval));
        v->type = LVAL_SEXPR;
        v->count = 0;
        v->cell = NULL;
        return v;
}

void
lval_del(lval* v) {
        int i;
        switch (v->type) {
        case LVAL_NUM:
                break;
        case LVAL_ERR:
                free(v->err);
                break;
        case LVAL_SYM:
                free(v->sym);
                break;
        case LVAL_SEXPR:
                for (i = 0; i < v->count; i++) {
                        lval_del(v->cell[i]);
                }
                free(v->cell);
                break;
        }
        free(v);
}

void 
lval_print(lval v) {
        switch (v.type) {
        /* In the case the type is a number print it */
        /* Then 'break' out of the switch. */
        case LVAL_NUM: printf("%li", v.num); break;

        /* In the case the type is an error */
        case LVAL_ERR:
        /* Check what type of error it is and print it */
        if (v.err == LERR_DIV_ZERO) {
                printf("Error: Division By Zero!");
        }
        if (v.err == LERR_BAD_OP)   {
                printf("Error: Invalid Operator!");
        }
        if (v.err == LERR_BAD_NUM)  {
                printf("Error: Invalid Number!");
        }
        break;
        }
}

/* Print an "lval" followed by a newline */
void 
lval_println(lval v) { 
        lval_print(v); 
        putchar('\n'); 
}
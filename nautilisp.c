#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "mpc.h"

int 
main(int argc, char** argv) {

    /* Create some parsers. */
    mpc_parser_t* number = mpc_new("number");
    mpc_parser_t* operator = mpc_new("operator");
    mpc_parser_t* expr = mpc_new("expr");
    mpc_parser_t* lisp = mpc_new("lisp");

    /* Define them with the following language. */
    mpca_lang(
        MPCA_LANG_DEFAULT,
        "
            number:     /-?[0-9]+/ ; \
            operator:   '+' | '-' | '*' | '/' ; \
            expr:       <number> | '(' <operator> <expr>+ ')' ; \
            lisp:       /^/ <operator> <expr>+ /$/ ; \
        ",
        number, operator, expr, lisp
    );
}
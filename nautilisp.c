#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "mpc/mpc.h"

long
eval_op(long x, char* op, long y) {
        if (strcmp(op, "+") == 0) { 
                return x + y; 
        } else if (strcmp(op, "-") == 0) { 
                return x - y; 
        } else if (strcmp(op, "*") == 0) { 
                return x * y; 
        } else if (strcmp(op, "/") == 0) { 
                return x / y; 
        }
        return 0;
}

long
eval(mpc_ast_t* t) {
        char* op;
        long x;
        int i;

        /* Base case: we hit a number, so return it! */
        if (strstr(t->tag, "number")) {
                return atoi(t->contents);
        }

        /* Recursive case: we hit an expression. */
        op = t->children[1]->contents;
        x = eval(t->children[2]);

        i = 3;
        while (strstr(t->children[i]->tag, "expr")) {
                x = eval_op(x, op, eval(t->children[i]));
                i++;
        }

        return x;
}

int 
main(int argc, char** argv) {

    /* Create Some Parsers */
        mpc_parser_t* number_parser   = mpc_new("number");
        mpc_parser_t* operator_parser = mpc_new("operator");
        mpc_parser_t* expr_parser     = mpc_new("expr");
        mpc_parser_t* lisp_parser     = mpc_new("lisp");
        
        /* Define them with the following Language */
        mpca_lang(MPCA_LANG_DEFAULT,
                "                                                   \
                number   : /-?[0-9]+/ ;                             \
                operator : '+' | '-' | '*' | '/' ;                  \
                expr     : <number> | '(' <operator> <expr>+ ')' ;  \
                lisp     : /^/ <operator> <expr>+ /$/ ;             \
                ",
                number_parser, operator_parser, expr_parser, lisp_parser);

        /* REPL */
        puts("Nautilisp v0.7");
        puts("Press Ctrl+C to quit.");

        while(1) {
                char* input;
                mpc_result_t r;

                /* Take some input. */
                putchar('\n');
                input = readline("> ");
                add_history(input);

                /* Try to parse it. */
                if (mpc_parse("<stdin>", input, lisp_parser, &r)) {
                        long result = eval(r.output);
                        printf("%li\n", result);
                        mpc_ast_delete(r.output);
                } else {
                        mpc_err_print(r.error);
                        mpc_err_delete(r.error);
                }

                free(input);
        }

        mpc_cleanup(
                4, 
                number_parser, 
                operator_parser, 
                expr_parser, 
                lisp_parser);

        return 0;
}
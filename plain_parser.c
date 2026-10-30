/* Basic parser, show's the structure but there is no code generation*/

#include<stdio.h>
#include"lex.h"

void factor(void);
void term(void);
void expression(void);
void term_prime(void);
void expression_prime(void);

void statements(){
    /*
     statement -> expression; | expression;statement;
     */
    expression();
    if(match(SEMI)){
        advance();
    }
    else{
        fprintf(stderr, "%d: missing semicolon\n", yylinenum);
    }
    if(!match(EOI)){
        statements();
    }
}

void expression(){
    /*
     expression -> term expression'
     */
    term();
    expression_prime();
}

void expression_prime(){
    /*
     expression' -> PLUS term expression' | epsilon
     */
    if(match(PLUS)){
        advance();
        term();
        expression_prime();
    }
}

void term(){
    /* term -> factor term'*/
    factor();
    term_prime();
}

void term_prime(){
    /* term' -> MULTIPLY factor term' | epsilon */
    if(match(MULTIPLY)){
        advance();
        factor();
        term_prime();
    }
}

void factor(){
    /* factor -> NUM_OR_ID | LP expression RP */
    if(match(NUM_OR_ID)){
        advance();
    }
    else if(match(LP)){
        advance();
        expression();
        if(match(RP)){
            advance();
        }
        else{
            fprintf(stderr, "%d: Missing Right Parenthesis\n", yylinenum);
        }
    }
    else{
        fprintf(stderr, "%d: Number or identifier expected\n", yylinenum);
    }
}

#include<stdio.h>
#include<stdarg.h>
#include"lex.h"
#define MAXFIRST 16
#define END SEMI

int legal_lookahead(int first_arg, ...){
    /*
     It checks if the next token makes sense i.e. belonging to the first set of expression ; if it doesn't, 
     it prints an error and skips bad tokens until it finds one that does. 
      */
    /* first set -> allowed tokens at the beginning of any nhon terminal */
    va_list arg;
    int lookahead[MAXFIRST];
    int *p = lookahead;
    int *current;
    int token;
    int error_printed = 0;
    int rval = 0;
    va_start(arg, first_arg);
    if(!first_arg){
        if(match(EOI)){
            rval = 1;
            return rval;
        }
    }
    else{
        *p++ = first_arg;
        while((token = va_arg(arg, int)) != 0 && p < &lookahead[MAXFIRST]){
            *p++ = token;
        }
        while(!match(END)){
            for(current = lookahead; current<p; current++){
                if(match(*current)){
                    rval=1;
                    return rval;
                }
            }
            if(!error_printed){
                fprintf(stderr, "Line %d: Syntax error\n", yylinenum);
            }
            advance();
        }
    }
    return rval;
}

void factor(void);
void term(void);
void expression(void);

void statements(void){
    /* statements -> expression; | expression;statements*/
    while(!match(EOI)){
        expression(); 
        if(match(SEMI)){
            advance();
        }
        else{
            fprintf(stderr, "%d: Missing semiclon\n", yylinenum);
        }
    }
}

void expression(){
    /* expression -> term expression'
       expression' -> PLUS term expression' | epsilon
    */
    if(!legal_lookahead(NUM_OR_ID, LP, 0)){
        return;
    }
    term();
    while(match(PLUS)){
        advance();
        term();
    }
}
void term(){
    if(!legal_lookahead(NUM_OR_ID, LP, 0)){
        return;
    }
    /*term -> factor term'
     term' -> TIMES factor term' | epsilon
    */
    factor();
    while(match(MULTIPLY)){
        advance();
        factor();
    }
}

void factor(){
    if(!legal_lookahead(NUM_OR_ID, LP, 0)){
        return;
    }
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
            fprintf(stderr, "%d: Missing Right Parenthesis\n",yylinenum);
        }
    }
    else{
        fprintf(stderr, "%d: Invalid input token\n", yylinenum);
    }
}

#include<stdio.h>
#include"lex.h"

void expression(char *tempvar);
void term(char *tempvar);
void factor(char *tempvar);

void statement(){
    /* statement -> expression SEMI | expression SEMI statement */

    char *tempvar;
    while(!match(EOI)){
        tempvar = newName();
        expression(tempvar);
        if(match(SEMI)){
            advance();
        }
        else{
            fprintf(stderr, "Line %d: Missing semicolon\n", yylinenum);
            break;
        }
    }
    return;
}

void expression(char *tempvar){
    /* expression -> term expression'
     expression' -> PLUS term expression' | epsilon
     */
    term(tempvar);
    char *tempvar2;
    while(match(PLUS)){
        advance();
        tempvar2 = newName();
        term(tempvar2);
        freeName(tempvar2);
    }
    return;
}

void term(char *tempvar){
    /* term -> factor term'
     term' -> MULTIPLY factor term' | epsilon
     */
    factor(tempvar);
    char *tempvar2;
    while(match(MULTIPLY)){
        advance();
        tempvar2 = newName();
        factor(tempvar2);
        freeName(tempvar2);
    }
    return;
}

void factor(char *tempvar){
    if(match(NUM_OR_ID)){
        printf("%s = %0.*s", tempvar, yylen, yytext);
        advance();
    }
    else if(match(LP)){
        advance();
        expression(tempvar);
        if(match(RP)){
            advance();
        }
        else{
            fprintf(stderr, "Line %d: Missing Right Parenthesis\n", yylinenum);
        }
    }
    else{
        fprintf(stderr, "Line %d: Invalid token\n", yylinenum);
    }
    return;
}

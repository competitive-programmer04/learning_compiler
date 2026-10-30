#include<stdio.h>
#include"lex.h"

char *factor(void);
char *term(void);
char *expression(void);

void statements(){
    /* statements -> expression SEMI  | expression SEMI statements */
    char *tempvar;
    while(!match(EOI)){
        tempvar = expression();
        if(match(SEMI)){
            advance();
        }
        else{
            fprintf(stderr, "Line %d: Missing semicolon\n", yylinenum);
            break;
        }
        freeName(tempvar);
    }
    return;
}

char *expression(){
    /* expression -> term expression'
     expression' -> PLUS term expression' | epsilon
     */
    char *tempvar1, *tempvar2;
    tempvar1 = term();
    while(match(PLUS)){
        advance();
        tempvar2 = term();
        printf("%s = %s + %s\n", tempvar1, tempvar1, tempvar2);
        freeName(tempvar2);
    }
    return tempvar1;
}

char *term(){
    /* term -> factor term'
     term' -> MULTIPLY factor term' | epsilon
     */
    char *tempvar1, *tempvar2;
    tempvar1 = factor();
    while(match(MULTIPLY)){
        advance();
        tempvar2 = factor();
        printf("%s = %s * %s\n", tempvar1, tempvar1, tempvar2);
        freeName(tempvar2);
    }
    return tempvar1;
}

char *factor(){
    char *tempvar1;
    if(match(NUM_OR_ID)){
        /* The .* will tell printf to print the maximum number of characters count from the next argument.
         i.e print yylen number of characters starting from yytext
         */
        printf("%s =  %0.*s\n", tempvar1 = newName(), yylen, yytext);
        advance();
    }

    else if(match(LP)){
        tempvar1 = expression();
        if(match(RP)){
            advance();
        }
        else{
            fprintf(stderr, "Line %d: Missing Right parenthesis\n", yylinenum);
        }
    }
    else{
        fprintf(stderr, "Invalide token at line: %d\n", yylinenum);
    }
    return tempvar1;
}

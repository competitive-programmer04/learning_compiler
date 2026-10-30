#include"lex.h"
#include<stdio.h>
#include<ctype.h>

char *yytext = ""; /* lexeme (not '\0' terminated) */
int yylen = 0;
int yylinenum = 0;

int lex(){
    static char input_buffer[128];
    char *current;
    current = yytext + yylen;
    while(1){
        while(!(*current)){
            // current is pointing to a blank line so we go to next input line and will skip all the empty spaces in that line
            current = input_buffer;
            if(input_buffer[0] == '\0'){
                *current = '\0';
                return EOI;
            }
            ++yylinenum;
            while(isspace(*current)){
                ++current;
            }
        }
            for(; *current; current++){
                yytext = current;
                yylen = 1;
                switch(*current){
                    case EOF:
                        return EOI;
                    case ';':
                        return SEMI;
                    case '+':
                        return PLUS;
                    case '*':
                        return MULTIPLY;
                    case '(':
                        return LP;
                    case ')':
                        return RP;
                    case '\n':
                    case '\t':
                    case ' ':
                        break;
                    default:
                        if(!isalnum(*current)){
                            fprintf(stderr, "Invalid input token\n");
                        }
                        else{
                            while(isalnum(*current)){
                                current++;
                            }
                            yylen = current - yytext;
                            return NUM_OR_ID;
                        }
                        break;
                }
            }
        }
    }

static int Lookahead = -1;
int match(int token){
    // matches Lookahead token(current input token) with its argument
    if(Lookahead == -1){
        Lookahead = lex();
    }
    return token == Lookahead;
}

void advance(){
    // advances to next token
    Lookahead = lex();
    return;
}

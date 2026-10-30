#include<stdio.h>
#include"lex.h"

char *Names[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7"}; /* stack for holding the
                                                                     names of temporary variables
                                                                     */
char **name_stack = Names; // stack pointer

/* used when want to allocate a new temporary variable */
char *newName(){
    if(name_stack >= &Names[sizeof(Names)/sizeof(*Names)]){
        fprintf(stderr, "Line %d: Stack Overflow\n", yylinenum);
        return NULL;
    }
    return (*name_stack++);
}

/* used when have to free existing temporary variable */
void freeName(char *name){
    if(name_stack <= Names){
        fprintf(stderr, "Line %d: Stack underflow\n", yylinenum);
    }
    else{
        *--name_stack = name;
    }
    return;
}

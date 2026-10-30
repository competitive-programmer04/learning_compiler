#define EOI 0   /* end of input */
#define SEMI 1  /* ; */
#define PLUS 2  /* + */
#define MULTIPLY 3  /*  *  */
#define LP 4  /* ( */
#define RP 5  /* ) */
#define NUM_OR_ID 6  /* 0-9 a-z A-Z */
 
extern char *yytext; // lexeme
extern int yylen;
extern int yylinenum;

int match(int token); /* matches current token with the token in its argument */
void advance(); /* moves to next token */
char *newName(); /* used to pop a new temporary variable from the stack */
void freeName(char *name); /* used to push back the temporary variable back to the stack */ 

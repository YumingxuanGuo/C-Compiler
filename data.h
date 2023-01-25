// Global variables.

#ifndef extern_
 #define extern_ extern
#endif

extern_ int     Line;
extern_ int     Putback;
extern_ FILE    *Inputfile;

extern_ struct token    Token;  // the most recent token scanned in from the input
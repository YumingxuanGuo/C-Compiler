// Global variables.

#ifndef extern_
#define extern_ extern
#endif

extern_ int    Line;
extern_ int    Putback;
extern_ FILE   *Inputfile;
extern_ FILE   *Outfile;
extern_ struct token Token;              // the most recent token scanned in from the input
extern_ char   Text[TEXTLEN + 1];        // last identifer scanned
extern_ struct symtable Gsym[NSYMBOLS];  // global symbol table
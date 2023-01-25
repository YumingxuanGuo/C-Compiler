// Lexical scanning.

#include "defs.h"
#include "data.h"
#include "decl.h"

// Get the next character from the input file.
static int next(void) {
    int c;

    // Return the put-back character if exists.
    if (Putback != 0) {
        c = Putback;
        Putback = 0;
        return c;
    }

    // Read from input file otherwise.
    c = fgetc(Inputfile);
    if (c == '\n') {
        Line++;
    }
    return c;
}

// Put back an unwanted character.
static void putback(int c) {
    Putback = c;
}

// Skip the whitespaces. Return the first next non-whitespace character.
static int skip(void) {
    int c;

    c = next();
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f') {
        c = next();
    }

    return c;
}

// Return the position of character c in string str, or -1 if c is not found.
int charpos(char *str, int c) {
    char *p = strchr(str, c);
    return p ? (p - str) : -1;
}

// Scan and return an integer literal value from the input file.
int scanint(int c) {
    int k, val = 0;

    // Keep reading each digit and calculate the value.
    // Applicable for hexadecimal digits as well.
    while ((k = charpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = next();
    }

    // Stopped at a non-integer character; put it back.
    putback(c);
    
    return val;
}

// Scan and return the next token found in the input.
// Return 1 if token valid, 0 if no tokens left.
int scan(struct token *t) {
    int c;

    // Skip whitespaces.
    c = skip();

    // Determine token based on input character.
    switch (c) {
    case EOF:
        t->token = T_EOF;
        return 0;
    case '+':
        t->token = T_PLUS;
        break;
    case '-':
        t->token = T_MINUS;
        break;
    case '*':
        t->token = T_STAR;
        break;
    case '/':
        t->token = T_SLASH;
        break;
    
    default:
        if (isdigit(c)) {
            t->intvalue = scanint(c);
            t->token = T_INTLIT;
            break;
        }
        printf("Unrecognised character %c on line %d\n", c, Line);
        exit(1);
    }

    return 1;
}
// Structure and enum definitions.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TEXTLEN  512   // max length of symbols in input
#define NSYMBOLS 1024  // max # of symbol table entries

// Tokens
enum {
    T_EOF, 
    T_PLUS, T_MINUS, 
    T_STAR, T_SLASH, 
    T_EQ, T_NE,
    T_LT, T_GT, T_LE, T_GE,
    T_INTLIT, T_ASSIGN, T_SEMI, T_IDENT,
    T_LBRACE, T_RBRACE, T_LPAREN, T_RPAREN,
    // Keywords
    T_PRINT, T_INT, T_IF, T_ELSE
};

// Token structure
struct token {
    int token;
    int intvalue;
};

// AST node types
enum {
    A_ADD=1, A_SUBTRACT, A_MULTIPLY, A_DIVIDE,
    A_EQ, A_NE, A_LT, A_GT, A_LE, A_GE,
    A_INTLIT,
    A_IDENT, A_LVIDENT, A_ASSIGN, A_PRINT,
    A_GLUE, A_IF
};

// Abstract Syntax Tree structure
//                   IF
//                 / |  \
//                /  |   \
//               /   |    \
//              /    |     \
//             /     |      \
//            /      |       \
//   condition   statements   statements
struct ASTnode {
    int op;                 // "operation" to be performed on this tree
    struct ASTnode *left;   // left child trees
    struct ASTnode *mid;
    struct ASTnode *right;
    union {
        int intvalue;  // for A_INTLIT, the integer value
        int id;        // for A_IDENT, the symbol slot number
    } v;
};

#define NOREG	-1  // Use NOREG when the AST generation functions have no register to return

// Symbol table structure
struct symtable {
    char *name;  // name of a symbol
};
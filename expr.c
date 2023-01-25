// Parsing of expressions

#include "defs.h"
#include "data.h"
#include "decl.h"

// Convert a token into an AST operation.
int arithop(int token) {
    switch (token) {
    case T_PLUS:
        return (A_ADD);
    case T_MINUS:
        return (A_SUBTRACT);
    case T_STAR:
        return (A_MULTIPLY);
    case T_SLASH:
        return (A_DIVIDE);
    default:
        fprintf(stderr, "unknown token in arithop() on line %d: token type = %d\n", Line, token);
        exit(1);
    }
}

// Parse a primary factor and return an AST node representing it.
static struct ASTnode *primary(void) {
    struct ASTnode *n;

    // For an INTLIT token, make a leaf AST node for it and scan in the next token.
    // Otherwise, a syntax error for any other token type.
    switch (Token.token) {
    case T_INTLIT:
        n = makeastleaf(A_INTLIT, Token.intvalue);
        scan(&Token);
        return (n);
    default:
        fprintf(stderr, "syntax error on line %d\n", Line);
        exit(1);
    }
}

// Return an AST tree whose root is a binary operator
struct ASTnode *binexpr(void) {
    struct ASTnode *n, *left, *right;
    int nodetype;

    // Get the integer literal on the left.
    left = primary();

    // If no tokens left, return just the left node.
    if (Token.token == T_EOF) {
        return left;
    }

    // Convert the token into a node type.
    nodetype = arithop(Token.token);

    // Read the next token in.
    scan(&Token);

    // Recurse into the right sub-tree.
    right = binexpr();

    // Build the root node with corressponding sub-trees.
    n = makeastnode(nodetype, left, right, 0);

    return n;
}
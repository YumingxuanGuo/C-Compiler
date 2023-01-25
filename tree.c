// AST tree functions.

#include "defs.h"
#include "data.h"
#include "decl.h"

// Build and return a generic AST node.
struct ASTnode *makeastnode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue) {
    struct ASTnode *n;

    // Malloc a new ASTnode.
    n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
    if (n == NULL) {
        fprintf(stderr, "Unable to malloc in mkastnode()\n");
        exit(1);
    }

    // Set the field values.
    n->op = op;
    n->left = left;
    n->right = right;
    n->intvalue = intvalue;

    return n;
}

// Make an AST leaf node.
struct ASTnode *makeastleaf(int op, int intvalue) {
  return (makeastnode(op, NULL, NULL, intvalue));
}

// Make a unary AST node: only one child (left as default).
struct ASTnode *makeastunary(int op, struct ASTnode *left, int intvalue) {
  return (makeastnode(op, left, NULL, intvalue));
}
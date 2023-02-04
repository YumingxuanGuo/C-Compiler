// Parsing of declarations

#include "defs.h"
#include "data.h"
#include "decl.h"

// Parse the declaration of a variable.
 void var_declaration(void) {
    // Ensure `int <identifier> ;`.
    match(T_INT, "int");
    ident();
    addglob(Text);
    genglobsym(Text);
    semi();
}

// function_declaration: 'void' identifier '(' ')' compound_statement   ;
//
// Parse a function declaration and return its AST.
struct ASTnode *function_declaration(void) {
    struct ASTnode *tree;
    int nameslot;

    // Match the `void`, identifier, and the `(` `)`.
    match(T_VOID, "void");
    ident();
    nameslot = addglob(Text);
    lparen();
    rparen();

    // Get the AST tree for the compound statement.
    tree = compound_statement();

    // Return an A_FUNCTION node with nameslot and compound statement as subtrees.
    return makeastunary(A_FUNCTION, tree, nameslot);
}

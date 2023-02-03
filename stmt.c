// Parsing of statements

#include "defs.h"
#include "data.h"
#include "decl.h"

// Prototypes
static struct ASTnode *single_statement(void);

// print_statement: 'print' expression ';'  ;
//
static struct ASTnode *print_statement(void) {
    struct ASTnode *tree;
    int reg;

    // Match a `print` as the first token.
    match(T_PRINT, "print");

    // Parse the following expression and generate the assembly.
    tree = binexpr(0);

    // Make an print AST tree.
    tree = makeastunary(A_PRINT, tree, 0);

    return (tree);
}

// assignment_statement: identifier '=' expression ';'   ;
//
static struct ASTnode *assignment_statement(void) {
    struct ASTnode *left, *right, *tree;
    int id;

    // Ensure we have an identifier.
    ident();

    // Check it has been defined, then make a leaf node for it.
    if ((id = findglob(Text)) == -1) {
        fatals("Undeclared variable", Text);
    }
    right = makeastleaf(A_LVIDENT, id);

    // Ensure we have an equals sign.
    match(T_ASSIGN, "=");

    // Parse the following expression.
    left = binexpr(0);

    // Make an assignment AST tree.
    tree = makeastnode(A_ASSIGN, left, NULL, right, 0);

    return tree;
}

// if_statement: if_head
//      |        if_head 'else' compound_statement
//      ;
//
// if_head: 'if' '(' true_false_expression ')' compound_statement  ;
//
// Parse an `if` statement including any option `else`, and return its AST.
struct ASTnode *if_statement(void) {
    struct ASTnode *condAST, *trueAST, *falseAST = NULL;

    // Match an `if` and a `(`.
    match(T_IF, "if");
    lparen();

    // Parse the condition expression.
    condAST = binexpr(0);

    // Ensure the condition expression's operation is a comparison.
    if (condAST->op < A_EQ || condAST->op > A_GE) {
        fatal("Bad comparison operator");
    }

    // Match the haning `)`.
    rparen();

    // Get the AST for the compound statement.
    trueAST = compound_statement();

    // If we have an `else`, skip it and get the following AST.
    if (Token.token == T_ELSE) {
        scan(&Token);
        falseAST = compound_statement();
    }

    // Build and return the final AST for this `if` statement.
    return makeastnode(A_IF, condAST, trueAST, falseAST, 0);
}

// while_statement: 'while' '(' true_false_expression ')' compound_statement  ;
//
// Parse a `while` statement and return its AST.
struct ASTnode *while_statement(void) {
    struct ASTnode *condAST, *bodyAST;

    // Match an `while` and a `(`
    match(T_WHILE, "while");
    lparen();

    // Parse the condition expression.
    condAST = binexpr(0);

    // Ensure the condition expression's operation is a comparison.
    if (condAST->op < A_EQ || condAST->op > A_GE) {
        fatal("Bad comparison operator");
    }

    // Match the haning `)`.
    rparen();

    // Generate the AST for the body.
    bodyAST = compound_statement();

    // Build and return the AST for this statement.
    return makeastnode(A_WHILE, condAST, NULL, bodyAST, 0);
}

// for_statement: 'for' '(' preop_statement ';'
//                          true_false_expression ';'
//                          postop_statement ')' compound_statement  ;

// preop_statement:  statement  ;        (for now)
// postop_statement: statement  ;        (for now)
//
// Parse a `for` statement and return its AST.
struct ASTnode *for_statement(void) {
    struct ASTnode *condAST, *bodyAST;
    struct ASTnode *preopAST, *postopAST;
    struct ASTnode *tree;

    // Match a `for` and a `(`.
    match (T_FOR, "for");
    lparen();

    // Get the pre_op statement and the `;`.
    preopAST = single_statement();
    semi();

    // Get the condition and the `;`.
    condAST = binexpr(0);
    if (condAST->op < A_EQ || condAST->op > A_GE) {
        fatal("Bad comparison operator");
    }
    semi();

    // Get the post_op statement and the `)`.
    postopAST = single_statement();
    rparen();

    // Get the body compound statement.
    bodyAST = compound_statement();

    // For now, all four sub-trees have to be non-NULL.
    // Later on, we'll change the semantics for when some are missing.

    //          A_GLUE
    //         /     \
    //    preop     A_WHILE
    //              /    \
    //         decision  A_GLUE
    //                   /    \
    //             compound  postop

    tree = makeastnode(A_GLUE, bodyAST, NULL, postopAST, 0);
    tree = makeastnode(A_WHILE, condAST, NULL, tree, 0);
    tree = makeastnode(A_GLUE, preopAST, NULL, tree, 0);

    return tree;
}

// Parse a single statement and return its AST.
static struct ASTnode *single_statement(void) {
    switch (Token.token) {
    case T_PRINT:
        return print_statement();
    case T_INT:
        var_declaration();
        return NULL;
    case T_IDENT:
        return assignment_statement();
    case T_IF:
        return if_statement();
    case T_WHILE:
        return while_statement();
    case T_FOR:
        return for_statement();
    
    default:
        fatald("Syntax error, token", Token.token);
    }
}

// compound_statement:          // empty, i.e. no statement
//      |      statement
//      |      statement statements
//      ;
//
// statement: print_statement
//      |     declaration
//      |     assignment_statement
//      |     if_statement
//      |     while_statement
//      |     for_statement
//      ;
//
// declaration: 'int' identifier ';'  ;
//
// identifier: T_IDENT ;
//
// Parse a compound statement and return its AST.
struct ASTnode *compound_statement(void) {
    struct ASTnode *left = NULL, *tree;

    // Match a left curly bracket.
    lbrace();

    while (1) {
        tree = single_statement();

        // For each new tree, either save it in the left (if left is NULL),
        // or make a new tree with left.
        if (tree) {
            if (tree->op == A_PRINT || tree->op == A_ASSIGN) {
                semi();
            }

            if (left == NULL) {
                left = tree;
            } else {
                left = makeastnode(A_GLUE, left, NULL, tree, 0);
            }
        }

        if (Token.token == T_RBRACE) {
            rbrace();
            return left;
        }
    }
}
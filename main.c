// Compiler setup and top-level execution.

#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

// List of printable tokens
char *tokstr[] = { "+", "-", "*", "/", "intlit" };

static void init(void) {
    Line = 1;
    Putback = '\n';
}

// Loop scanning in all the tokens in the input file.
// Print out details of each token found.
static void scanfile() {
  struct token T;

  while (scan(&T)) {
    printf("Token %s", tokstr[T.token]);
    if (T.token == T_INTLIT) {
      printf(", value %d", T.intvalue);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
    struct ASTnode *tree;
    init();

    if ((Inputfile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    // Create the output file
    if ((Outfile = fopen("out.s", "w")) == NULL) {
        fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
        exit(1);
    }

    scan(&Token);	                  // Get the first token from the input.
    genpreamble();                    // Output the preamble.
    while (1) {
        tree = function_declaration();  // Parse the statements from the input.
        genAST(tree, NOREG, 0);       // Generate the assembly code for it
        if (Token.token == T_EOF) {
            break;
        }
    }

    fclose(Outfile);
    exit(0);
}
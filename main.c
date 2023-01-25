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
    Putback = '\n';
    Line = 1;
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
    init();

    if ((Inputfile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    scanfile();

    exit(0);
}
// Symbol table functions

#include "defs.h"
#include "data.h"
#include "decl.h"

static int Globs = 0;  // position of next free global symbol slot

// Determine if symbol `str` is in the global symbol table.
// Return its slot position or -1 if not found.
int findglob(char *str) {
    int i;
    for (i = 0; i < Globs; i++) {
        if (strcmp(str, Gsym[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

// Get the position of a new global symbol slot.
// Panic if we've run out of positions.
static int newglob(void) {
    int pos;
    if ((pos = Globs++) >= NSYMBOLS) {
        fatal("Too many symbols");
    }
    return pos;
}

// Add a global symbol to the symbol table.
// Return the slot number in the symbol table.
int addglob(char *name) {
    int pos;
    if ((pos = findglob(name)) != -1) {
        return pos;
    }
    pos = newglob();
    Gsym[pos].name = strdup(name);
    return pos;
}
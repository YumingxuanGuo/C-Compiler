// Function prototypes for all compiler files.

// scan.c
int scan(struct token *t);

// tree.c
struct ASTnode *makeastnode(int op, struct ASTnode *left,
			  struct ASTnode *right, int intvalue);
struct ASTnode *makeastleaf(int op, int intvalue);
struct ASTnode *makeastunary(int op, struct ASTnode *left, int intvalue);

// expr.c
struct ASTnode *binexpr(int ptp);
struct ASTnode *multiplicative_expr(void);
struct ASTnode *additive_expr(void);

// gen.c
int genAST(struct ASTnode *n);
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);

// cg.c
void freeall_registers(void);
void cgpreamble();
void cgpostamble();
int cgload(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);

// stmt.c
void statements(void);

// misc.c
void match(int t, char *what);
void semi(void);
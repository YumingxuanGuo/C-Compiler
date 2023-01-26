// Function prototypes for all compiler files.

int scan(struct token *t);
struct ASTnode *makeastnode(int op, struct ASTnode *left,
			  struct ASTnode *right, int intvalue);
struct ASTnode *makeastleaf(int op, int intvalue);
struct ASTnode *makeastunary(int op, struct ASTnode *left, int intvalue);
struct ASTnode *multiplicative_expr(void);
struct ASTnode *additive_expr(void);
struct ASTnode *binexpr(void);

int interpretAST(struct ASTnode *n);
void generatecode(struct ASTnode *n);

void freeall_registers(void);
void cgpreamble();
void cgpostamble();
int cgload(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);

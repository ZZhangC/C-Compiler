// scan.c
int scan(struct token *t);

// tree.c
struct astNode *mkASTNode(struct astNode *left, struct astNode *right, int op, int intValue);
struct astNode *mkASTLeaf(int op, int intValue);
struct astNode *mkASTUnary(struct astNode *left, int op, int intValue);

// expr.c
struct astNode *binExpr(int parPrec);

// intp.c
//int interpretAST(struct astNode *n);

// gen.c
int procAST(struct astNode *n);
void genPreamble();
void genPostamble();
void genFreeRegs();
void genPrintInt(int reg);

// asm.c
void setAllRegFree(void);
void genASMPreamble();
void genASMPostamble();
int genASMLoad(int value);
int genASMAdd(int r1, int r2);
int genASMSub(int r1, int r2);
int genASMMul(int r1, int r2);
int genASMDiv(int r1, int r2);
void genASMPrintInt(int r);

// stmt.c
void statements(void);

// misc.c
void matchToken(int t, char *str);
void matchSemi(void);

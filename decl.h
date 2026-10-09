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
int procAST(struct astNode *n, int reg);
void genPreamble(void);
void genPostamble(void);
void genFreeRegs(void);
void genPrintInt(int reg);
void genGlobSym(char *s);

// asm.c
void setAllRegFree(void);
void genASMPreamble(void);
void genASMPostamble(void);
int genASMLoad(int value);
int genASMLoadGlob(char *ident);
int genASMAdd(int r1, int r2);
int genASMSub(int r1, int r2);
int genASMMul(int r1, int r2);
int genASMDiv(int r1, int r2);
void genASMPrintInt(int r);
int genASMStorGlob(int r, char *ident);
void genASMGlobSym(char *sym);
int genASMEqual(int r1, int r2);
int genASMNotEqual(int r1, int r2);
int genASMLessThan(int r1, int r2);
int genASMGreatThan(int r1, int r2);
int genASMLessEqual(int r1, int r2);
int genASMGreatEqual(int r1, int r2);

// stmt.c
void statements(void);

// misc.c
void matchToken(int t, char *str);
void matchSemi(void);
void matchIdent(void);
void fatal(char *s);
void fatals(char *s1, char *s2);
void fatald(char *s, int d);
void fatalc(char *s, int c);

// sym.c
int findGlob(char *s);
int addGlob(char *name);

// decl.c
void varDecl(void);

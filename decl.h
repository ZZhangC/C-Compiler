int scan(struct token *t);

struct astNode *mkASTNode(struct astNode *left, struct astNode *right, int op, int intValue);
struct astNode *mkASTLeaf(int op, int intValue);
struct astNode *mkASTUnary(struct astNode *left, int op, int intValue);
struct astNode *binExpr(int parPrec);

int interpretAST(struct astNode *n);
void genAST(struct astNode *n);

void genASM(struct astNode *n);
void freeAllReg(void);
void genASMPreamble();
void genASMPostamble();
int genASMLoad(int value);
int genASMAdd(int r1, int r2);
int genASMSub(int r1, int r2);
int genASMMul(int r1, int r2);
int genASMDiv(int r1, int r2);
void genASMPrintInt(int r);

int scan(struct token *t);
struct astNode *mkASTNode(struct astNode *left, struct astNode *right, int op, int intValue);
struct astNode *mkASTLeaf(int op, int intValue);
struct astNode *mkASTUnary(struct astNode *left, int op, int intValue);
struct astNode *binExpr(int parPrec);
int interpretAST(struct astNode* n);

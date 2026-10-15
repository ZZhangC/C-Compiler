#include "defs.h"
#include "data.h"
#include "decl.h"

static struct astNode *stmtPrint() {
	struct astNode *tree;
	int reg;

	matchToken(T_PRINT, "printf");

	tree = binExpr(0);
	reg = procAST(tree, -1);
	genPrintInt(reg);
	genFreeRegs();

	matchSemi();

	return tree;
}

static struct astNode *stmtAssign(void) {
	struct astNode *left, *right, *tree;
	int id;

	matchIdent();

	id = findGlob(buf);
	if (id == -1)
		fatals("Undeclared variable", buf);

	right = mkASTLeaf(A_LVALIDENT, id);

	matchToken(T_ASSIGN, "=");

	left = binExpr(0);

	tree = mkASTNode(left, NULL, right, A_ASSIGN, 0);

	procAST(tree, -1);
	genFreeRegs();

	matchSemi();
	return tree;
}

static struct astNode *stmtIf() {
	struct astNode *nodeCond, *nodeTrue, *nodeFalse = NULL;

	matchToken(T_IF, "if");
	matchLparen();

	nodeCond = binExpr(0);

	if (nodeCond->op < A_EQUALS && nodeCond->op > A_GREATEQUAL)
		fatal("Bad comparison operator");

	matchRparen();

	nodeTrue = stmtCompound();

	if (currToken.token == T_ELSE) {
		scan(&currToken);
		nodeFalse = stmtCompound();
	}

	return mkASTNode(nodeCond, nodeTrue, nodeFalse, A_IF, 0);
}

static struct astNode *stmtCompound(void) {
	struct astNode *left = NULL;
	struct astNode *tree;

	matchLbrace();

	while (1) {
		switch (currToken.token) {
			case T_PRINT:
				tree = stmtPrint();
				break;
			case T_INT:
				varDecl();
				tree = NULL;
				break;
			case T_IDENT:
				tree = stmtAssign();
				break;
			case T_IF:
				tree = stmtIf();
				break;
			case T_RBRACE:
				matchRbrace();
				return left;
			default:
				fatald("Syntax error, token", currToken.token);
		}

		if (tree) {
			if (left == NULL)
				left = tree;
			else
				left = mkASTNode(left, NULL, tree, A_GLUE, 0);
		}
	}
}

void statements(void) {
	while (1) {
		switch (currToken.token) {
			case T_PRINT:
				stmtPrint();
				break;
			case T_INT:
				varDecl();
				break;
			case T_IDENT:
				stmtAssign();
				break;
			case T_EOF:
				return;
			default:
				fatald("Syntax error, token", currToken.token);
		}
	}
}

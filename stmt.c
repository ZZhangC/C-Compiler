#include "defs.h"
#include "data.h"
#include "decl.h"

void stmtPrint() {
	struct astNode *tree;
	int reg;

	matchToken(T_PRINT, "printf");

	tree = binExpr(0);
	reg = procAST(tree, -1);
	genPrintInt(reg);
	genFreeRegs();

	matchSemi();
}

void stmtAssign(void) {
	struct astNode *left, *right, *tree;
	int id;

	matchIdent();

	id = findGlob(buf);
	if (id == -1)
		fatals("Undeclared variable", buf);

	right = mkASTLeaf(A_LVALIDENT, id);

	matchToken(T_EQUALS, "=");

	left = binExpr(0);

	tree = mkASTNode(left, right, A_ASSIGN, 0);

	procAST(tree, -1);
	genFreeRegs();

	matchSemi();
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

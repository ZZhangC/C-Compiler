#include "defs.h"
#include "data.h"
#include "decl.h"

void statements(void) {
	struct astNode *tree;
	int reg;

	while (1) {
		matchToken(T_PRINT, "printf");

		tree = binExpr(0);
		reg = procAST(tree);
		genPrintInt(reg);
		genFreeRegs();

		matchSemi();
		if (currToken.token == T_EOF)
			break;
	}
}

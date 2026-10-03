#include "defs.h"
#include "data.h"
#include "decl.h"

// Generate ASM code from ASTs
static int procAST(struct astNode *n) {
	int leftReg, rightReg;

	if (n->left) leftReg = procAST(n->left);
	if (n->right) rightReg = procAST(n->right);

	switch (n->op) {
		case A_ADD: return genASMAdd(leftReg, rightReg);
		case A_SUBTRACT: return genASMSub(leftReg, rightReg);
		case A_MULTIPLY: return genASMMul(leftReg, rightReg);
		case A_DIVIDE: return genASMDiv(leftReg, rightReg);
		case A_INTLIT: return genASMLoad(n->intValue);

		default:
			fprintf(stderr, "Unknown AST operation %d\n", n->op);
			exit(1);
	}
}

// Generate whole ASM code
void genASM(struct astNode *n) {
	int reg;

	genASMPreamble();
	reg = procAST(n);
	genASMPrintInt(reg);
	genASMPostamble();
}

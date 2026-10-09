#include "defs.h"
#include "data.h"
#include "decl.h"

// Front-end codes
void genPreamble() { genASMPreamble(); }
void genPostamble() { genASMPostamble(); }
void genFreeRegs() { setAllRegFree(); }
void genPrintInt(int reg) { genASMPrintInt(reg); }
void genGlobSym(char *sym) { genASMGlobSym(sym); }

// Generate ASM code from ASTs
int procAST(struct astNode *n, int reg) {
	int leftReg, rightReg;

	if (n->left) leftReg = procAST(n->left, -1);
	if (n->right) rightReg = procAST(n->right, leftReg);

	switch (n->op) {
		case A_ADD:
			return genASMAdd(leftReg, rightReg);
		case A_SUBTRACT:
			return genASMSub(leftReg, rightReg);
		case A_MULTIPLY:
			return genASMMul(leftReg, rightReg);
		case A_DIVIDE:
			return genASMDiv(leftReg, rightReg);
		case A_INTLIT:
			return genASMLoad(n->val.intValue);
		case A_IDENT:
			return genASMLoadGlob(globSym[n->val.id].name);
		case A_LVALIDENT:
			return genASMStorGlob(reg, globSym[n->val.id].name);
		case A_ASSIGN:
			return rightReg;
		case A_EQUALS:
			return genASMEqual(leftReg, rightReg);
		case A_NOTEQUAL:
			return genASMNotEqual(leftReg, rightReg);
		case A_LESSTHAN:
			return genASMLessThan(leftReg, rightReg);
		case A_GREATTHAN:
			return genASMGreatThan(leftReg, rightReg);
		case A_LESSEQUAL:
			return genASMLessEqual(leftReg, rightReg);
		case A_GREATEQUAL:
			return genASMGreatEqual(leftReg, rightReg);

		default:
			fprintf(stderr, "Unknown AST operation %d\n", n->op);
			exit(1);
	}
}


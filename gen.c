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
int procAST(struct astNode *n, int reg, int parOp) {
	int leftReg, rightReg;

	switch (n->op) {
		case A_IF:
			return genASMIf(n);
		case A_GLUE:
			procAST(n->left, NOREG, n->op);
			genFreeRegs();
			procAST(n->right, NOREG, n->op);
			genFreeRegs();
			return NOREG;
	}

	if (n->left) leftReg = procAST(n->left, NOREG, n->op);
	if (n->right) rightReg = procAST(n->right, leftReg, n->op);

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
		case A_NOTEQUAL:
		case A_LESSTHAN:
		case A_GREATTHAN:
		case A_LESSEQUAL:
		case A_GREATEQUAL:
			if (parOp == A_IF)
				return genASMCmpAndJmp(n->op, leftReg, rightReg, reg);
			else
				return genASMCmpAndSet(n->op, leftReg, rightReg);
		

		default:
			fprintf(stderr, "Unknown AST operation %d\n", n->op);
			exit(1);
	}
}

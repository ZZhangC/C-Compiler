#include "defs.h"
#include "data.h"
#include "decl.h"

int interpretAST(struct astNode *n) {
	int leftVal, rightVal;

	if (n->left)
		leftVal = interpretAST(n->left);
	if (n->right)
		rightVal = interpretAST(n->right);

	switch (n->op) {
		case A_ADD:
			return leftVal + rightVal;
		case A_SUBTRACT:
			return leftVal - rightVal;
		case A_MULTIPLY:
			return leftVal * rightVal;
		case A_DIVIDE:
			return leftVal / rightVal;
		case A_INTLIT:
			return n->intValue;
		default:
			fprintf(stderr, "Unknown AST operator on Line %d\n", line);
			exit(1);
	}
}

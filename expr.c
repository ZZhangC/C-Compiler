#include "defs.h"
#include "data.h"
#include "decl.h"

// Build the first AST node
static struct astNode *getPrimaryNode(void) {
	struct astNode *n;
	
	switch (currToken.token) {
		case T_INTLIT:
			n = mkASTLeaf(A_INTLIT, currToken.intValue);
			scan(&currToken);
			return n;
		default:
			fprintf(stderr, "Syntax error on Line %d\n", line);
			exit(1);
	}
}

// Convert a token to an AST operation
int tokenToASTOp(int token) {
	switch (token) {
		case T_PLUS:
			return A_ADD;
		case T_MINUS:
			return A_SUBTRACT;
		case T_STAR:
			return A_MULTIPLY;
		case T_SLASH:
			return A_DIVIDE;
		default:
			fprintf(stderr, "Unknown token in tokenToASTOp() on Line %d\n", line);
			exit(1);
	}
}

// Build an uninterpreted AST tree
// This function is only for binary expressions for now
struct astNode *unintpASTTree(void) {
	struct astNode *n, *left, *right;
	int nodeType;

	left = getPrimaryNode();

	if (currToken.token == T_EOF)
		return left;

	nodeType = tokenToASTOp(currToken.token);
	
	scan(&currToken);

	right = unintpASTTree();

	n = mkASTNode(left, right, nodeType, 0);

	return n;
}


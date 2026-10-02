#include "defs.h"
#include "data.h"
#include "decl.h"

// Build and return a generic AST node
struct astNode *mkASTNode(struct astNode *left, struct astNode *right, int op, int intValue) {
	struct astNode *n;
	n = (struct astNode *)malloc(sizeof(struct astNode));

	if (n == NULL) {
		fprintf(stderr, "Unable to malloc in mkASTNode()\n");
		exit(1);
	}

	n->left = left;
	n->right = right;
	n->op = op;
	n->intValue = intValue;

	return n;
}

// Build and return an AST leaf node
struct astNode *mkASTLeaf(int op, int intValue) {
	return mkASTNode(NULL, NULL, op, intValue);
}

// Build and return a unary AST node
struct astNode *mkASTUnary(struct astNode *left, int op, int intValue) {
	return mkASTNode(left, NULL, op, intValue);
}


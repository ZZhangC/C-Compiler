#include "defs.h"
#include "data.h"
#include "decl.h"

static int opPrec[] = {0, 1, 1, 2, 2, 0};

// Return the precedence of an operator
static int getOpPrec(int tokenType) {
	int prec = opPrec[tokenType];
	if (prec == 0) {
		fprintf(stderr, "Syntax error on line %d, token %d\n", line, tokenType);
		exit(1);
	}
	return prec;
}

// Build the first AST node
static struct astNode *getPrimaryNode(void) {
	struct astNode *n;
	int id;
	
	switch (currToken.token) {
		case T_INTLIT:
			n = mkASTLeaf(A_INTLIT, currToken.intValue);
			break;
		case T_IDENT:
			id = findGlob(buf);
			if (id == -1)
				fatals("Unknown variable", buf);
			n = mkASTLeaf(A_IDENT, id);
			break;
		default:
			fatald("Syntax error, token", currToken.token);
			exit(1);
	}
	scan(&currToken);
	return n;
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




// -------  Incorrect Method ------- //
// This method can not fix the probl //
// em of precedence                  //
// This would not be updated after 0 //
// 3 Precedence                      //
// -------                   ------- //
// Build an uninterpreted AST tree
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
// -------    Warning    ------- //
// This method has a bad extensi //
// bility                        //
// This would not be updated aft //
// er 03 Precedence              //
// -------               ------- //
// Process with multiplicative expressions
struct astNode *multiplicativeExpr(void) {
	struct astNode *left, *right;
	int tokenType;

	left = getPrimaryNode();
	
	tokenType = currToken.token;

	if (tokenType == T_EOF)
		return left;

	while (tokenType == T_STAR || tokenType == T_SLASH) {
		scan(&currToken);

		right = getPrimaryNode();
		left = mkASTNode(left, right, tokenToASTOp(tokenType), 0);

		tokenType = currToken.token;
		if (tokenType == T_EOF)
			break;
	}

	return left;
}
// Process with additive expressions
struct astNode *additiveExpr(void) {
	struct astNode *left, *right;
	int tokenType;

	left = multiplicativeExpr();

	tokenType = currToken.token;

	if (tokenType == T_EOF)
		return left;

	while (1) {
		scan(&currToken);
		
		right = multiplicativeExpr();
		left = mkASTNode(left, right, tokenToASTOp(tokenType), 0);

		tokenType = currToken.token;
		if (tokenType == T_EOF)
			break;
	}
}




// A better method for processing binary expressions
struct astNode *binExpr(int parPrec) {
	struct astNode *left, *right;
	int tokenType;

	left = getPrimaryNode();

	tokenType = currToken.token;
	
	if (tokenType == T_EOF || tokenType == T_SEMI)
		return left;

	while (getOpPrec(tokenType) > parPrec) {
		scan(&currToken);

		right = binExpr(getOpPrec(tokenType));
		left = mkASTNode(left, right, tokenToASTOp(tokenType), 0);

		tokenType = currToken.token;
		if (tokenType == T_EOF || tokenType == T_SEMI)
			return left;
	}

	return left;
}

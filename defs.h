#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFLEN 512

enum { T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_PRINT };

enum { A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT };

struct token {
	int token;
	int intValue;
};

struct astNode {
	struct astNode *left;
	struct astNode *right;
	int op;
	int intValue;
};


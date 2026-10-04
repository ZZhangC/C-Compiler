#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFLEN 512

enum { T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_EQUALS, T_IDENT, T_PRINT, T_INT };

enum { A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT, A_IDENT, A_LVALIDENT, A_ASSIGN };

struct token {
	int token;
	int intValue;
};

struct astNode {
	struct astNode *left;
	struct astNode *right;
	int op;
	union {
		int intValue;
		int id;
	} val;
};

struct symTable {
	char *name;
};

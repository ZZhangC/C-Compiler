#include "defs.h"
#include "data.h"
#include "decl.h"

// Process with input stream
static int next(void) {
	int c;

	if (putBack) {
		//debug
		printf("putback: %c\n", putBack);
		//
		c = putBack;
		putBack = 0;
		return c;
	}

	c = fgetc(inFile);
	if ('\n' == c)
		line++;
	return c;
}

static void putBackChar(int c) {
	putBack = c;
}

// Skip blank characters
static int skip(void) {
	int c;

	c = next();
	while (' ' == c || '\n' == c || '\r' == c || '\t' == c || '\f' == c)
		c = next();
	return c;
}


// Scan integer literal values
static int chrPos(const char* s, int c) {
	const char *p;

	p = strchr(s, c);
	return p ? (p - s) : -1;
}

static int scanInt(int c) {
	int k, val = 0;

	while ((k = chrPos("0123456789", c)) >= 0) {
		val = val * 10 + k;
		c = next();
	}

	putBackChar(c);
	return val;
}

// Entrance of token scanning function
int scan(struct token *t) {
	int c;

	c = skip();

	switch (c) {
		case EOF:
			t->token = T_EOF;
			break;
		case '+':
			t->token = T_PLUS;
			break;
		case '-':
			t->token = T_MINUS;
			break;
		case '*':
			t->token = T_STAR;
			break;
		case '/':
			t->token = T_SLASH;
			break;
		default:
			if (isdigit(c)) {
				t->token = T_INTLIT;
				t->intValue = scanInt(c);
				break;
			}
			//debug
			printf("Unrecognised character %c on Line %d\n", c, line);
			exit(1);
	}

	return 1;
}


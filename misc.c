#include "defs.h"
#include "data.h"
#include "decl.h"

void matchToken(int t, char *str) {
	if (currToken.token == t) {
		scan(&currToken);
	}
	else {
		printf("%s expected on Line %d\n", str, line);
		exit(1);
	}
}

void matchSemi(void) { matchToken(T_SEMI, ";"); }
void matchIdent(void) { matchToken(T_IDENT, "Identifier"); }

void fatal(char *s) {
	fprintf(stderr, "%s on Line %d\n", s, line);
	exit(1);
}
void fatals(char *s1, char *s2) {
	fprintf(stderr, "%s: %s on Line %d\n", s1, s2, line);
	exit(1);
}
void fatald(char *s, int d) {
	fprintf(stderr, "%s: %d on Line %d\n", s, d, line);
	exit(1);
}
void fatalc(char *s, int c) {
	fprintf(stderr, "%s: %c on Line %d\n", s, c, line);
	exit(1);
}

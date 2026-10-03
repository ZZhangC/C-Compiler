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

void matchSemi(void) {
	matchToken(T_SEMI, ";");
}

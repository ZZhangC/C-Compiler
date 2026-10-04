#include "defs.h"
#include "data.h"
#include "decl.h"

static int globs = 0;

int findGlob(char *s) {
	for (int i = 0; i < globs; i++) {
		if (*s == *globSym[i].name && !strcmp(s, globSym[i].name))
			return i;
	}
	return -1;
}

static int newGlob(void) {
	int p;
	p = globs++;
	if (p >= NSYMBOLS)
		fatal("Too many global symbols");
	return p;
}

int addGlob(char *name) {
	int y;

	y = findGlob(name);
	if (y != -1)
		return y;

	y = newGlob();
	globSym[y].name = strdup(name);
	return y;
}

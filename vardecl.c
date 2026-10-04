#include "defs.h"
#include "data.h"
#include "decl.h"

void varDecl(void) {
	matchToken(T_INT, "int");
	matchIdent();
	addGlob(buf);
	genGlobSym(buf);
	matchSemi();
}

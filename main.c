#include <errno.h>
#include "defs.h"
#define extern_
	#include "data.h"
#undef extern_
#include "decl.h"

static void init(void) {
	line = 1;
	putBack = 0;
}

static void usage(char *prog) {
	fprintf(stderr, "Usage: %s infile\n", prog);
	exit(1);
}

int main(int argc, char* argv[]) {
	if (argc != 2)
		usage(argv[0]);

	init();
	
	inFile = fopen(argv[1], "r");
	if (inFile == NULL) {
		fprintf(stderr, "Unable to open %s\n", argv[1], strerror(errno));
		exit(1);
	}

	struct astNode *n;

	scan(&currToken);
	n = unintpASTTree();
	int res = interpretAST(n);
	printf("Result: %d\n", res);

	exit(0);
}

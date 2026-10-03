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
		fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	outFile = fopen("out.s", "w");
	if (outFile == NULL) {
		fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
		exit(1);
	}

	scan(&currToken);
	genPreamble();
	statements();
	genPostamble();
	
	fclose(outFile);

	exit(0);
}

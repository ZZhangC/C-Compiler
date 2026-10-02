#include <errno.h>
#include "defs.h"
#define extern_
	#include "data.h"
#undef extern_
#include "decl.h"

static void init(void) {
	line = 1;
	putBack = '\n';
}

//debug
char *tokStr[] = { "+", "-", "*", "/", "INTLIT" };
//


void scanFile(void) {
	struct token T;
	
	//debug
	while (scan(&T)) {
		printf("Token %s\n", tokStr[T.token]);
		if (T.token == T_INTLIT) {
			printf("Value %d\n", T.intValue);
		}
		printf("\n");
	}
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

	scanFile();

	exit(0);
}

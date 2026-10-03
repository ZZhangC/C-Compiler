#ifndef extern_
	#define extern_ extern
#endif

extern_ int line;
extern_ int putBack;
extern_ FILE *inFile;
extern_ FILE *outFile;
extern_ struct token currToken;
extern_ char buf[BUFLEN + 1];

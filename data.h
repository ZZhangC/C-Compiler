#ifndef extern_
	#define extern_ extern
#endif

#define NSYMBOLS 1024

extern_ int line;
extern_ int putBack;
extern_ FILE *inFile;
extern_ FILE *outFile;
extern_ struct token currToken;
extern_ char buf[BUFLEN + 1];
extern_ struct symTable globSym[NSYMBOLS];

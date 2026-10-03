scan:
	cc -o scanner -g main.c, scan.c

parse:
	cc -o parser -g expr.c intp.c main.c scan.c tree.c

asm:
	cc -o asm -g asm.c expr.c intp.c tree.c gen.c main.c scan.c

clean:
	rm -f scanner parser asm out.s *.o

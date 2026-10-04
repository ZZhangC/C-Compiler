var:
	cc -o var -g asm.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c vardecl.c

test1:
	cc -o var -g asm.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c vardecl.c
	./var ./Tests/test1
	cc -o out out.s
	./out

clean:
	rm -f var out.s out *.o

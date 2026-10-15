comp:
	cc -o comp -g asm.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c vardecl.c

test1:
	cc -o comp -g asm.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c vardecl.c
	./comp ./Tests/test1
	cc -o out out.s
	./out

clean:
	rm -f comp out.s out *.o

comp:
	cc -o comp -g asm.c expr.c gen.c main.c misc.c scan.c stmt.c tree.c

test1:
	cc -o comp -g asm.c expr.c gen.c main.c misc.c scan.c stmt.c tree.c
	./comp ./Tests/test1
	cc -o out out.s
	./out

clean:
	rm -f comp out.s out *.o

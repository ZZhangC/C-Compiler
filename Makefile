scan:
	cc -o scanner -g main.c, scan.c

parse:
	cc -o parser -g expr.c intp.c main.c scan.c tree.c

clean:
	rm -f scanner parser *.o

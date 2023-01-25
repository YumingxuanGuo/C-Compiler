parser: expr.c interp.c main.c scan.c tree.c
	cc -o parser -g expr.c interp.c main.c scan.c tree.c

parser2: expr2.c interp.c main.c scan.c tree.c
	cc -o parser2 -g expr2.c interp.c main.c scan.c tree.c
clean:
	rm -f parser parser2 *.o

test: parser
	-(./parser tests/input01; \
	 ./parser tests/input02; \
	 ./parser tests/input03; \
	 ./parser tests/input04; \
	 ./parser tests/input05)

test2: parser2
	-(./parser2 input01; \
	 ./parser2 input02; \
	 ./parser2 input03; \
	 ./parser2 input04; \
	 ./parser2 input05)

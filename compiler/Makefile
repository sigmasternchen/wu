
%.o: %.c
	clang -std=c99 -Wall -D_POSIX_C_SOURCE=201112L -D_XOPEN_SOURCE=500 -D_GNU_SOURCE -g -MMD -c -o $@ $<

wuc: lexer.o parser.o codegen.o llvm.o compiler.o
	clang -o $@ $^

all: wuc example

example: example.wu wuc
	./wuc -o example.o example.wu
	clang -o example example.o

clean:
	rm -f *.o
	rm -f wuc
	rm -f example

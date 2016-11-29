
DEPS=syn.c stack.c

all: interp lexer tests

interp: interp.c $(DEPS)


lexer: lexer.c $(DEPS)

tests: interp lexer
	$(info NO TESTS)

clean:
	rm *.o lexer interp
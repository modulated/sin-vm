CC=clang
CFLAGS=-std=c11 -Wall -pedantic -I$(HEADER_DIR)
DEPS=source/stack.c source/sin.c
HEADER=$(wildcard include/*.h)
HEADER_DIR=include
OBJECTS=$(patsubst %.c, %.o, $(SOURCE))


PARSEIN=source/sin-cc.y
LEXIN=source/sin-cc.l
LEXOUT=source/cc-lexer.yy.c
PARSEOUT=source/cc-parser.tab.c


VM=build/sin-vm
ASM=build/sin-asm
COM=build/sin-cc

all: $(COM) $(VM) $(ASM) tests

com: $(COM)	
	build/sin-cc
	
$(ASM): $(DEPS) $(HEADER) source/sin-asm.c
	$(CC) $(CFLAGS) -o $(ASM) $(DEPS) source/sin-asm.c 

$(VM): $(DEPS) $(HEADER) source/sin-vm.c
	$(CC) $(CFLAGS) -o $(VM) $(DEPS) source/sin-vm.c 

$(COM): $(DEPS) $(HEADER) $(PARSEOUT) $(LEXOUT) $(PARSEIN) $(LEXIN) source/sin-cc.c
	$(CC) $(CFLAGS) -o $(COM) $(LEXOUT) $(PARSEOUT) source/sin-cc.c $(DEPS)

$(LEXOUT): $(LEXIN)
	flex -o $(LEXOUT) $(LEXIN) 

$(PARSEOUT): $(PARSEIN)
	bison -d -o $(PARSEOUT) $(PARSEIN)

tests: $(VM) $(ASM)
	sh test/test.sh

clean:
	rm $(LEXOUT) $(PARSEOUT)
	rm -r -- build/sin-*

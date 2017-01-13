CC=clang
CFLAGS=-std=c11 -Wall -pedantic -I$(HEADER_DIR)
DEPS=source/stack.c source/sin.c
HEADER=$(wildcard include/*.h)
HEADER_DIR=include
OBJECTS=$(patsubst %.c, %.o, $(SOURCE))
LEX=source/cc-lexer.yy.c
PARSE=source/cc-parser.tab.c


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

$(COM): $(DEPS) $(HEADER) $(PARSE) $(LEX) source/sin-cc.c
	$(CC) $(CFLAGS) -o $(COM) $(LEX) $(PARSE) source/sin-cc.c $(DEPS)

$(LEX): source/sin-cc.l
	flex -o $(LEX) source/sin-cc.l 

$(PARSE): source/sin-cc.y
	bison -d source/sin-cc.y -o $(PARSE)

tests: $(VM) $(ASM)
	sh test/test.sh

clean:
	rm $(LEX) $(PARSE)
	rm -r -- build/sin-*

CFLAGS=-std=c99 -g -Wall -pedantic -I$(HEADER_DIR)
DEPS=source/stack.c source/sin.c
HEADER=$(wildcard include/*.h)
HEADER_DIR=include
OBJECTS=$(patsubst %.c, %.o, $(SOURCE))

VM=build/sin-vm
ASSEMBLER=build/sin-assembler


all: $(VM) $(ASSEMBLER) tests

$(ASSEMBLER): $(DEPS) $(HEADER) source/assembler.c
	$(CC) $(CFLAGS) -o $(ASSEMBLER) $(DEPS) source/assembler.c 

$(VM): $(DEPS) $(HEADER) source/vm.c
	$(CC) $(CFLAGS) -o $(VM) $(DEPS) source/vm.c 

tests: $(VM) $(ASSEMBLER)
	$(info NO TESTS)

clean:
	rm source/*.o build/*

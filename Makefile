CFLAGS=-std=c99 -g -Wall -pedantic -I$(HEADER_DIR)
DEPS=source/stack.c source/sin.c
HEADER=$(wildcard include/*.h)
HEADER_DIR=include
OBJECTS=$(patsubst %.c, %.o, $(SOURCE))

VM=build/sin-vm
ASM=build/sin-asm


all: $(VM) $(ASM) tests

$(ASM): $(DEPS) $(HEADER) source/sin-asm.c
	$(CC) $(CFLAGS) -o $(ASM) $(DEPS) source/sin-asm.c 

$(VM): $(DEPS) $(HEADER) source/sin-vm.c
	$(CC) $(CFLAGS) -o $(VM) $(DEPS) source/sin-vm.c 

tests: $(VM) $(ASM)
	$(info NO TESTS)

clean:
	rm source/*.o build/*

#ifndef SIN_H
#define SIN_H


#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define STACK_SIZE 256
#define OUTPUT_SIZE 4

stack_int_t stack;
int output[OUTPUT_SIZE];

#define POP stack_pop(&stack)
#define PEEK stack_peek(&stack)
#define PUSH(x) stack_push(&stack, x)

/* BASIC OPCODES */
#define SRT	0x53594E2E // Start of op codes
#define	END 	0xFFFFFFFF // End of op codes
#define	NOP 	0x00000000 // No operation
#define	SET 	0x00000002 // Push value onto stack
#define	GET 	0x00000003 // Return value from stack into output register
#define CLR 	0x00000004 // Clear top value from output register

/* CONTROL FLOW */
#define JMP 	0x0000000A // Jump to program buffer address
#define JPO 	0x0000000B // Jump to program buffer address of next value if stack zero 
#define JZE 	0x0000000C // Jump to program buffer address of next value if stack zero 
#define JNE 	0x0000000D // Jump to program buffer address of next value if stack zero 

/* MATHS */
#define INC	0x00000100 // Increment first stack element
#define DEC	0x00000101 // Decrement first stack element
#define	ADD 	0x0000010A // Add first two stack elements
#define	SUB 	0x0000010B // Subtract second element from first
#define	MUL 	0x0000010C // Multiply first two stack elements
#define	DIV 	0x0000010D // Divide first element by second
#define	MOD 	0x0000010E // Modulo division
#define LTH 	0x00000111 // First stack less than second stack element
#define GTH 	0x00000112 // First stack greater than second stack element
#define LTE 	0x00000113 // First stack less than or equal to second stack element
#define GTE 	0x00000114 // First stack greater than or equal to second stack element

/* MEMORY - variables and heap */ 

/* STRINGS */
#define PST 	0x00000101 // Push string onto stack in reverse order
#define GST 	0x00000102 // Get nul terminated string off stack in order

/* INPUT & OUTPUT */
#define INI 	0x00F00001 // Add int from stdin to stack
#define OUT 	0x00F00011 // Print int from stack to stdout

enum SYN_ERROR {
	ERR_UNKNOWN_ERROR = -4,
	ERR_OUTPUT_OVERFLOW,
	ERR_ILLEGAL_INSTRUCTION,
	ERR_STACK_OVERFLOW,
};

int* read_file(char* file);
void dump_program(int* prog);
void dump_output();
int endian_swap(int in);
void endian_swap_buffer(int* buffer);
size_t get_filesize(char* file);
void print_error(int error);
int execute_program(int* input, int* output);
void instruction_toupper(char* code);
int sancode_to_sincode(char* code);

#endif

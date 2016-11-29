#ifndef SIN_OPS_H
#define SIN_OPS_H

#include "sin.h" 

int op_get () {
	#ifdef DEBUG
		puts("GET");
	#endif

	return POP;
}

void op_set (int x) {
	#ifdef DEBUG
		puts("SET");
	#endif

	PUSH(x);
}

void op_clr () {
	#ifdef DEBUG
		puts("CLR");
	#endif


}

void op_add () {
	#ifdef DEBUG
		puts("ADD");
	#endif

	PUSH(POP + POP);
}

void op_sub() {
	PUSH(POP - POP);

	#ifdef DEBUG
		puts("SUB");
	#endif
}

void op_mul() {
	PUSH(POP * POP);
	
	#ifdef DEBUG
		puts("MUL");
	#endif
}

void op_div() {
	PUSH(POP / POP);
	
	#ifdef DEBUG
		puts("DIV");
	#endif
}

void op_mod() {
	PUSH(POP % POP);
	
	#ifdef DEBUG
		puts("MOD");
	#endif
}

void op_ini() {
	#ifdef DEBUG
		puts("INI");
	#endif

	int i = 0;
	scanf("%d", &i);
	PUSH(i);
}

void op_out() {
	#ifdef DEBUG
		puts("OUT");
	#endif

	printf("%d\n", POP);
}

#endif

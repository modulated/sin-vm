#include "sin.h"

int yylex();

int main() {
	puts("SIN-CC Compiler");
	puts("");

	printf("%d\n", yylex());
}
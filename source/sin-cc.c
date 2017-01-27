#include "sin.h"

char* infilestr;
FILE* infilefp;
extern FILE* yyin;

int yylex();
int yyparse();

void checkparse() {
	int res = yyparse();
	if (res == 0) puts("Parse success.");
	else puts("ERROR: Parse failed.");
}

int main(int argc, char** argv) {
	puts("SIN-CC Compiler");
	puts("");
	
	if (argc == 1)
		checkparse();
	
	else if (argc == 2) {

		infilestr = malloc((strlen(argv[1]) + 1) * sizeof(char));
		strcpy(infilestr, argv[1]);
		infilefp = fopen(infilestr, "r");
		yyin = infilefp;

		checkparse();
	}

	else {
		puts("ERROR: please provide 0 - 1 args");
		exit(1);
	}

  puts("");
	return 0;
}



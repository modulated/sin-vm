#include "sin.h"

char* infilestr;
FILE* infilefp;
extern FILE* yyin;

int yylex();
int yyparse();

int main(int argc, char** argv) {
	puts("SIN-CC Compiler");
	puts("");
	
	if (argc == 1)
		printf("%d\n", yyparse());
	
	else if (argc == 2) {

		infilestr = malloc((strlen(argv[1]) + 1) * sizeof(char));
		strcpy(infilestr, argv[1]);
		infilefp = fopen(infilestr, "r");
		yyin = infilefp;

    printf("%d\n", yyparse());

		// int res = 1;
		// while (res != 0) {
		// 	res = yylex();
		// 	printf("%d\n", res);
		// } 
	}

	else {
		puts("ERROR: please provide 0 - 1 args");
		exit(1);
	}

  puts("");
	return 0;
}



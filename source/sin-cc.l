%{
	#include <stdlib.h>
	#include "cc-parser.tab.h"
	
	void yyerror(char* s);
	int fileno(FILE* f);
	int yywrap() {
		return 1;
	}
%}

%%
[0-9]+	{ // Int
	yylval.i = atoi(yytext);
	return INT;
}

= {
	return EQ;
}

[a-zA-Z]+([a-zAZ0-9_]+)? {
	yylval.s = (yytext);	
	return ID;
}

%%

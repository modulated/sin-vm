%{
	#include <stdlib.h>
	#include "cc-parser.tab.h"
	
	void yyerror(char* s);
	
	int yywrap() {
		return 1;
	}
%}

%%
[0-9]+	{ // Int
	yylval.i = atoi(yytext);
	return INT;
}

[0-9]+\.[0-9]+	{ // Real
	yylval.r = atof(yytext);
	return REAL;
}

= {
	return EQ;
}

[a-zA-Z]+[a-zAZ0-9_]+ {
	yylval.s = (yytext);	
	return ID;
}

%%

%{
	#include <stdlib.h>
	#include <string.h>
	#include "cc-parser.tab.h"
	
	void yyerror(char* s);
	int fileno(FILE* f);
	int yywrap() {
		return 1;
	}
	int line_num = 1;
%}

%option nounput
%option noinput

%%

[0-9]+	{ // Int
	yylval.i = atoi(yytext);
	return INT;
}

"print" return PRINT;

[a-zA-Z]+([a-zAZ0-9_]+)? {
	yylval.s = (yytext);	
	return ID;
}

"+" return PLUS;
"-" return MINUS;
"*" return STAR;
"/" return F_SLASH;
"=" return EQUAL;
"(" return L_PAREN;
")" return R_PAREN;
"<" return L_ANGLE;
">" return R_ANGLE;

\n { ++line_num; return NEWLINE; }
[\t ] ;
<<EOF>> return END_OF_FILE;

. { printf("Unmatched sequence: %s\n", yytext); }

%%

%{
	#include <stdio.h>
	int yylex();	
	void yyerror(const char *s);
%}

%union {
	int i;
	char* s;
}

%token INT
%token EQ
%token ID

%type<i> INT expr 
%type<s> ID stat line

%%

program:
	// Empty program
	| program line
	| line
	;

line:
	stat '\n' { $$ = $1; }	
	;

stat:
	ID '=' expr { printf("%s = %d\n", yyval.s, $3); }


expr:
	INT { $$ = $1; }
	| ID { printf("ID: %s\n",$1); }
	;

%%

void yyerror(const char* s) {
	fprintf(stderr, "%s\n", s);

}

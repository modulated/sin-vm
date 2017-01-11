%{
	#include <stdio.h>
	int yylex();	
	void yyerror(char *s);
%}

%union {
	int i;
	unsigned int u;
	float r;
	char* s;
}

%token INT
%token REAL
%token EQ
%token ID

%type<i> INT expr
%type<r> REAL
%type<s> ID stat line

%%

program:
	program 
	| line
	;

line:
	stat '\n' { $$ = $1 ;}
	| expr '\n' { $$ = $1 ;}
	;

stat:
	ID '=' expr { printf("%s set to %d\n", yyval.s, $3); }


expr:
	INT { $$ = $1; }
	| ID { $$ = $1; }
	;

%%

void yyerror(char* s) {
	fprintf(stderr, "%s\n", s);
}
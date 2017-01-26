%{
	#include <stdio.h>
	#include "ast.h"	

	int yylex();
	void yyerror(const char *s);
	extern int line_num;
	extern node_t tree;
	

%}


%union {
	int i;
	char* s;
}

%token INT
%token ID
%token EQUAL PLUS MINUS STAR F_SLASH
%token R_PAREN L_PAREN L_ANGLE R_ANGLE
%token NEWLINE END_OF_FILE

%type<i> INT expr 
%type<s> ID

// Operator precedence
%left PLUS

%start program
%%

program:
	// Empty
	| term
	| statlist term
	;

term:
	NEWLINE END_OF_FILE
	| END_OF_FILE
	;

statlist:
	stat
	| statlist NEWLINE stat
	;

stat:
	ID EQUAL expr { printf("%s = %d\n", $1, $3); }
	| ID EQUAL ID { printf("%s = %s\n", $1, $3); }
	| expr { printf("LONE EXPR\n"); }
	;


expr:
	INT { printf("INT: %d\n", yylval.i); $$ = yylval.i; }
	| ID { printf("ID: %s\n", yylval.s); $$ = 0; }
	;

%%

void yyerror(const char* s) {
	fprintf(stderr, "ERROR: %i: %s\n", line_num, s);

}

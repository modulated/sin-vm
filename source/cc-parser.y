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
%token PRINT
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
	| expr { }
	| PRINT expr { printf("%d\n", $2); }
	;


expr:
	INT { $$ = yylval.i; }
	| ID { $$ = 0; }
	;

%%

void yyerror(const char* s) {
	fprintf(stderr, "ERROR: %i: %s\n", line_num, s);

}

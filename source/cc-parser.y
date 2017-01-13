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
%token ID
%token EQUAL PLUS
%token R_PAREN L_PAREN
%token NEWLINE END_OF_FILE

%type<i> INT expr 
%type<s> ID

// Operator precedence
%left PLUS

%start program
%%

program:
	// Empty program
	| statlist
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
	INT { printf("INT: %d\n", yylval.i); }
	| ID { printf("ID: %s\n", yylval.s); }
	;

%%

void yyerror(const char* s) {
	fprintf(stderr, "%s\n", s);

}

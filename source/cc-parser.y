%{
	#include <stdio.h>	
	#include <string.h>	
	#include "siphash.h"

	int yylex();
	void yyerror(const char *s);
	extern int line_num;
	
	int ht[0xFF] = {0};
	void sethash(char* key, int val);
	int gethash(char* key);

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

%type<i> INT expr assignment
%type<s> ID

// Operator precedence
%left PLUS

%start program
%%

program:
	// Empty	
	| statlist NEWLINE
	| statlist END_OF_FILE
	;


statlist:
	stat
	| statlist NEWLINE stat
	;

stat:

	| expr { printf("%d\n", $1); }
	| PRINT expr { printf("%d\n", $2); }
	| ID { printf("%s\n", yylval.s); }
	;


expr:
	assignment
	| INT { $$ = yylval.i; }
	| L_PAREN ID R_PAREN { $$ = gethash(yylval.s); }
	;

assignment:
	ID EQUAL expr { sethash("a", $3); $$ = $3; }
	| ID MINUS EQUAL expr { $$ = $4; }
	;
%%

void yyerror(const char* s) {
	fprintf(stderr, "ERROR: %i: %s\n", line_num, s);

}

void sethash(char* key, int val) {
	
	uint8_t kp[8] = "roadslut";
	uint8_t out[8];
	siphash((unsigned char*)key, 1, kp, out, 8);
	
	// printf("%d: %d\n", out[0], val);
	ht[out[0]] = val;
}

int gethash(char* key) {
	
	uint8_t kp[8] = "roadslut";
	uint8_t out[8];
	siphash((unsigned char*)key, 1, kp, out, 8);
	
	// printf("%d: %d\n", out[0], ht[out[0]]);
	return ht[out[0]];
}
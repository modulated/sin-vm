#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>
#include "../source/cc-parser.tab.h"

typedef struct node_s {
	struct node_s* root;
	struct node_s* left;
	struct node_s* right;
	int token;
	union {
		int i;
		char* s;
	} data;
} node_t;


node_t ast_node(node_t* root, node_t* left, node_t* right, int token, void* data);
node_t ast_new();
node_t* ast_root(node_t* node);


#endif

	

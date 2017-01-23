#include "ast.h"
#include "cc-parser.tab.h"


node_t ast_node(node_t* root, node_t* left, node_t* right, int token, void* data) {
	node_t n;
	n.root = root;
	n.left = left;
	n.right = right;
	n.token = token;
	
	switch (token) {
		case INT:
			n.data.i = *(int*)data;
			break;
		case ID:
			n.data.s = (char*)data;
			break;
	
		default:
			break;
	}

	return n;
}

node_t ast_new() {
	return ast_node(NULL, NULL, NULL, -1, NULL);
}

node_t* ast_root(node_t* node) {
	node_t* t = node;
	while (t->root != NULL) {
		t = t->root;
	}
	return t;
}
	

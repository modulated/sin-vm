#include "ast.h"
#include "../source/cc-parser.tab.h"

int main() {
	int a = 12;
	node_t r = ast_new();
	node_t l = ast_node(&r, NULL, NULL, INT, &a);
	node_t* t = ast_root(&l);

	printf("%p should equal %p\n", &r, t);
	printf("n: %d\n", l.data.i);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
	int a[] = {4, 5, 12, 13, 87, 12, 85, 9, 0};
	SearchTree *tree = tree_build_from_array(a, sizeof(a) / sizeof(a[0]));
	tree_clear(tree);
	free(tree);
	return 0;
}
#include <stdlib.h>
#include "tree.h"

void tree_make_empty(SearchTree *tree)
{
	if (!tree)
		return;
	tree->root = NULL;
	tree->size = 0;
}
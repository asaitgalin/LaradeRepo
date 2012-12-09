#ifndef _TREE_H_
#define _TREE_H_

/* Binary Search Tree for integers */

struct TreeNode_Tag;

struct TreeNode_Tag
{
	int value;
	struct TreeNode_Tag *left;
	struct TreeNode_Tag *right;
	struct TreeNode_Tag *parent;
};

typedef struct TreeNode_Tag TreeNode;

typedef struct
{
	TreeNode *root;
	unsigned int size;
}SearchTree;

void tree_make_empty(SearchTree *tree);
int tree_insert(SearchTree *tree, int value);
int tree_insert_left(SearchTree *tree, TreeNode *pos, int value);
int tree_insert_right(SearchTree *tree, TreeNode *pos, int value);
TreeNode *tree_find(SearchTree *tree, int value);
SearchTree *tree_build_from_array(int *a, int n);
int tree_size(SearchTree *tree);
void tree_remove_subtree(SearchTree *tree, TreeNode *node);
void tree_clear(SearchTree *tree);
void tree_print(SearchTree *tree);

#endif
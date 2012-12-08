#ifndef _TREE_H_
#define _TREE_H_

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

#endif
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

void tree_make_empty(SearchTree *tree)
{
	if (!tree)
		return;
	tree->root = NULL;
	tree->size = 0;
}

int tree_insert_left(SearchTree *tree, TreeNode *pos, int value)
{
	TreeNode *node = NULL;
	if (!pos || !tree)
		return 0;
	if (pos->left || (value > pos->value))
		return 0;
	node = (TreeNode *)calloc(1, sizeof(TreeNode));
	if (!node)
		return 0;
	node->value = value;
	node->parent = pos;
	pos->left = node;
	tree->size++;
	return 1;
}

int tree_insert_right(SearchTree *tree, TreeNode *pos, int value)
{
	TreeNode *node = NULL;
	if (!pos || !tree)
		return 0;
	if (pos->right || (value < pos->value))
		return 0;
	node = (TreeNode *)calloc(1, sizeof(TreeNode));
	if (!node)
		return 0;
	node->value = value;
	node->parent = pos;
	pos->right = node;
	tree->size++;
	return 1;
}

int tree_insert(SearchTree *tree, int value)
{
	TreeNode *node = NULL;
	TreeNode *current = NULL;
	TreeNode *p = NULL;
	if (!tree)
		return 0;
	node = (TreeNode *)calloc(1, sizeof(TreeNode));
	if (!node)
		return 0;
	node->value = value;
	current = tree->root;
	while(current)
	{
		p = current;
		if (current->value < value)
			current = current->right;
		else if (current->value > value)
			current = current->left;
		else if (current->value == value)
			goto value_exists;
	}
	node->parent = p;
	if (!p)
		tree->root = node;
	else
	{
		if (node->value < p->value)
			p->left = node;
		else
			p->right = node;
	}
	tree->size++;
	return 1;
value_exists:
	free(node);
	return 1;
}

int tree_size(SearchTree *tree)
{
	if (!tree)
		return 0;
	return tree->size;
}

TreeNode *tree_find(SearchTree *tree, int value)
{
	TreeNode *node = NULL;
	if (!tree)
		return NULL;
	node = tree->root;
	while(node)
	{
		if (node->value == value)
			return node;
		else
		{
			if (node->value < value)
				node = node->right;
			else
				node = node->left;
		}	
	}
	return NULL;
}

SearchTree *tree_build_from_array(int *a, int n)
{
	SearchTree *tree = NULL;
	int i;
	tree = (SearchTree *)calloc(1, sizeof(SearchTree));
	if (!tree)
		return NULL;
	for (i = 0; i < n; ++i)
		tree_insert(tree, a[i]);
	return tree;
}

void tree_remove_subtree(SearchTree *tree, TreeNode *node)
{
	if (!node)
		return;
	if (node->left)
		tree_remove_subtree(tree, node->left);
	if (node->right)
		tree_remove_subtree(tree, node->right);
	if (!node->left && !node->right)
	{
		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = NULL;
			if (node->parent->right == node)
				node->parent->right = NULL;
		}
		if (tree->root == node)
			tree->root = NULL;
		free(node);
		tree->size--;
	}
}

void tree_clear(SearchTree *tree)
{
	if (!tree)
		return;
	tree_remove_subtree(tree, tree->root);
}

void tree_print_branch(TreeNode *node, int depth)
{
	int i;
	for (i = 0; i < depth * 2; ++i)
		printf(" ");
	printf("%d\n", node->value);
	if (node->left)
		tree_print_branch(node->left, depth + 1);
	if (node->right)
		tree_print_branch(node->right, depth + 1);
}

void tree_print(SearchTree *tree)
{
	if (tree_size(tree) == 0)
		return;
	tree_print_branch(tree->root, 0);
}


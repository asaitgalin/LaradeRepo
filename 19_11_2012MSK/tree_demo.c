#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

const char *err_str = "Syntax error!";
const char *help_str = "size\n"
					   "clear\n"
					   "insert\n"
					   "insert_right\n"
					   "insert_left\n"
					   "jump_root\n"
					   "jump_left\n"
					   "jump_right\n"
					   "jump_parent\n"
					   "remove_subtree\n"
					   "current\n"
					   "find\n"
					   "print\n"
					   "quit";

const char *node_err = "Tree node doesn't exist";
const char *insert_err = "Insertion error!";

enum insert_position
{
	ipWholeTree = 0,
	ipNodeLeft,
	ipNodeRight
};

int get_one_arg(char *args, int *arg)
{
	if (!args)
	{
		printf("%s\n", err_str);
		return 0;
	}
	if (sscanf(args, "%d", arg) != 1)
	{
		printf("%s\n", err_str);
		return 0;
	}
	return 1;
}

void insert(char *args, SearchTree *tree, TreeNode *current, int position)
{
	int n;
	if (get_one_arg(args, &n))
	{
		switch(position)
		{
		case ipWholeTree:
			if (!tree_insert(tree, n))
				printf("%s\n", insert_err);
			break;
		case ipNodeLeft:
			if (!tree_insert_left(tree, current, n))
				printf("%s\n", insert_err);
			break;
		case ipNodeRight:
			if (!tree_insert_right(tree, current, n))
				printf("%s\n", insert_err);
			break;
		}
	}
}

void print_value(TreeNode *node)
{
	if (!node)
	{	
		printf("%s\n", node_err);
		return;
	}
	printf("Value: %d\n", node->value);
}

void find(char *args, SearchTree *tree, TreeNode **out)
{
	int n;
	if (get_one_arg(args, &n))
	{
		TreeNode *node = tree_find(tree, n);
		if (node)
			*out = node;
		else
			printf("%s\n", node_err);
	}
}

int main()
{
	char buf[256];
	char *cmd = NULL, *args = NULL;
	SearchTree tree;
	TreeNode *current = NULL;	
	tree_make_empty(&tree);
	while(1)
	{
		printf("> ");
		fgets(buf, sizeof(buf), stdin);
		cmd = strtok(buf, " \n");
		args = strtok(NULL, "\n");
		if (!cmd)
			continue;
		if (!strcmp(cmd, "quit"))
			break;
		else if (!strcmp(cmd, "clear"))
			tree_clear(&tree);
		else if (!strcmp(cmd, "help"))
			printf("%s\n", help_str);
		else if (!strcmp(cmd, "size"))
			printf("Size: %d\n", tree_size(&tree));	
		else if (!strcmp(cmd, "insert"))
			insert(args, &tree, current, ipWholeTree);
		else if (!strcmp(cmd, "insert_left"))
			insert(args, &tree, current, ipNodeLeft);
		else if (!strcmp(cmd, "insert_right"))
			insert(args, &tree, current, ipNodeRight);
		else if (!strcmp(cmd, "jump_root"))
			current = tree.root;
		else if (!strcmp(cmd, "jump_left")) {
			if (current)
				if (current->left)
					current = current->left;
		}
		else if (!strcmp(cmd, "jump_right")) {
			if (current)
				if (current->right)
					current = current->right;
		}
		else if (!strcmp(cmd, "jump_parent")) {
			if (current)
				if (current->parent)
					current = current->parent;
		}
		else if (!strcmp(cmd, "find"))
			find(args, &tree, &current);
		else if (!strcmp(cmd, "remove_subtree")) {
			tree_remove_subtree(&tree, current);
			current = NULL;
		}
		else if (!strcmp(cmd, "current"))
			print_value(current);
		else if (!strcmp(cmd, "print"))
			tree_print(&tree);
		else
			printf("Command \"%s\" not found\n", cmd);
	}
	tree_clear(&tree);
	return 0;
}
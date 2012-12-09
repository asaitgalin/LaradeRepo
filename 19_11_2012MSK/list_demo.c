#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

const char *err_str = "Syntax error!";
const char *help_str = "General functions:\n"
					   "size\n"
					   "clear\n"
					   "push_back\n"
					   "push_front\n"
					   "pop_back\n"
					   "pop_front\n"
					   "front\n"
					   "back\n"
					   "print\n"
					   "quit\n\n"
					   "Additional functions:\n"
					   "current\n"
					   "jump_first\n"
					   "jump_last\n"
					   "jump_next\n"
					   "jump_prev\n"
					   "remove\n"
					   "insert_after\n"
					   "insert_before";

const char *node_err = "List is empty or node doesn't exist";

enum push_direction
{
	pd_front = 0,
	pd_back
};

enum insert_direction
{
	id_before = 0,
	id_after
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

void push(char *args, List *list, int pd)
{
	int n;
	if (get_one_arg(args, &n))
	{
		if (pd == pd_front)
			list_push_front(list, n);
		else
			list_push_back(list, n);
	}
}

void pop(char *args, List *list, Node **current, int pd)
{
	int n;
	if (pd == pd_front)
	{
		if (*current == list->first)
			*current = NULL;
		if (list_pop_front(list, &n))
			printf("%d\n", n);
	}
	else
	{
		if (*current == list->last)
			*current = NULL;
		if (list_pop_back(list, &n))
			printf("%d\n", n);
	}
}

void insert(char *args, List *list, Node *node, int direction)
{
	int n;
	if (get_one_arg(args, &n))
	{
		if (direction == id_after)
			list_insert_after(list, node, n);
		else 
			list_insert_before(list, node, n);
	}		
}

void print_value(Node *node)
{
	if (!node)
	{	
		printf("%s\n", node_err);
		return;
	}
	printf("Value: %d\n", node->value);
}

int main()
{
	char buf[256];
	char *cmd = NULL, *args = NULL;
	List list;
	Node *current = NULL;	
	list_make_empty(&list);
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
			list_clear(&list);
		else if (!strcmp(cmd, "help"))
			printf("%s\n", help_str);
		else if (!strcmp(cmd, "size"))
			printf("Size: %d\n", list_get_size(&list));	
		else if (!strcmp(cmd, "push_back"))
			push(args, &list, pd_back);
		else if (!strcmp(cmd, "current"))
			print_value(current);
		else if (!strcmp(cmd, "jump_first"))
			current = list.first;
		else if (!strcmp(cmd, "jump_last"))
			current = list.last;
		else if (!strcmp(cmd, "jump_next")) {
			if (current)		
				if (current->next)
					current = current->next;
		}
		else if (!strcmp(cmd, "jump_prev")) {
			if (current)
				if (current->prev)
					current = current->prev;
		}
		else if (!strcmp(cmd, "print"))
			list_print(&list);
		else if (!strcmp(cmd, "remove")) {
			list_remove(&list, current);
			current = NULL;
		}
		else if (!strcmp(cmd, "insert_after"))
			insert(args, &list, current, id_after);
		else if (!strcmp(cmd, "insert_before"))
			insert(args, &list, current, id_before);
		else if (!strcmp(cmd, "pop_back"))
			pop(args, &list, &current, pd_back);
		else if (!strcmp(cmd, "pop_front"))
			pop(args, &list, &current, pd_front);
		else if (!strcmp(cmd, "push_front"))
			push(args, &list, pd_front);
		else if (!strcmp(cmd, "front"))
			print_value(list.first);
		else if (!strcmp(cmd, "back"))
			print_value(list.last);
		else
			printf("Command \"%s\" not found\n", cmd);
	}
	list_clear(&list);
	return 0;
}
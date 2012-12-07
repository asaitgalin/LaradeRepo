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
					   "current";

const char *list_err = "List doesn't exist!";
const char *node_err = "List is empty or node doesn't exist";

enum push_direction
{
	pd_front = 0,
	pd_back
};

void push(char *args, List *list, int pd)
{
	int n;
	if (!args)
	{
		printf("%s\n", err_str);
		return;
	}
	if (sscanf(args, "%d", &n) == 1)
	{
		if (pd == pd_front)
			list_push_front(list, n);
		else
			list_push_back(list, n);
	}
	else
		printf("%s\n", err_str);
}

void pop(char *args, List *list, int pd)
{
	int n;
	if (pd == pd_front)
	{
		if (list_pop_front(list, &n))
			printf("%d\n", n);
	}
	else
	{
		if (list_pop_back(list, &n))
			printf("%d\n", n);
	}
}

void print_value(List *list, Node *node)
{
	if (!list)
	{
		printf("%s\n", list_err);
		return;
	}
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
			print_value(&list, current);
		else if (!strcmp(cmd, "move_front"))
			current = list.first;
		else if (!strcmp(cmd, "move_back"))
			current = list.last;
		else if (!strcmp(cmd, "move_next")) {
			if (current->next)
				current = current->next;
			else
				printf("Next node doesn't exist\n");
		}
		else if (!strcmp(cmd, "move_prev")) {
			if (current->prev)
				current = current->prev;
			else
				printf("Prev node doesn't exist\n");
		}
		else if (!strcmp(cmd, "print"))
			list_print(&list);
		else if (!strcmp(cmd, "remove"))
			list_remove(&list, current);
		/*else if (!strcmp(cmd, "insert_after"))
			list_insert_after(&list, current, 
		*/else if (!strcmp(cmd, "pop_back"))
			pop(args, &list, pd_back);
		else if (!strcmp(cmd, "pop_front"))
			pop(args, &list, pd_front);
		else if (!strcmp(cmd, "push_front"))
			push(args, &list, pd_front);
		else if (!strcmp(cmd, "front"))
			print_value(&list, list.first);
		else if (!strcmp(cmd, "back"))
			print_value(&list, list.last);
		else
			printf("Command \"%s\" not found\n", cmd);
	}
	list_clear(&list);
	return 0;
}
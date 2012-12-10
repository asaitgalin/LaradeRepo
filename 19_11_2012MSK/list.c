#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void list_make_empty(List *list)
{
	if (!list)
		return;
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
}

int list_push_front(List *list, int value)
{
	Node *node = NULL;
	if (!list)
		return 0;
	node = (Node *)calloc(1, sizeof(Node));
	if (!node)
		return 0;
	node->value = value;
	node->next = list->first;
	if (list->first)
		list->first->prev = node;
	list->first = node;
	if (node->next)
		node->next->prev = node;
	if (!list->last)
		list->last = node;
	list->size++;
	return 1;
}

int list_push_back(List *list, int value)
{
	Node *node = NULL;
	if (!list)
		return 0;
	node = (Node *)calloc(1, sizeof(Node));
	if (!node)
		return 0;
	node->value = value;
	node->prev = list->last;
	if (list->last)
		list->last->next = node;
	list->last = node;
	if (node->prev)
		node->prev->next = node;
	if (!list->first)
		list->first = node;
	list->size++;
	return 1;
}

int list_insert_after(List *list, Node *pos, int value)
{
	Node *node = NULL;
	if (!list || !pos)
		return 0;
	node = (Node *)malloc(sizeof(Node));
	if (!node)
		return 0;
	node->value = value;
	node->next = pos->next;
	node->prev = pos;
	if (pos->next)
		pos->next->prev = node;
	pos->next = node;
	if (pos == list->last)
		list->last = node;
	list->size++;
	return 1;
}

int list_insert_before(List *list, Node *pos, int value)
{
	Node *node = NULL;
	if (!list || !pos)
		return 0;
	node = (Node *)malloc(sizeof(Node));
	if (!node)
		return 0;
	node->value = value;
	node->next = pos;
	node->prev = pos->prev;
	if (pos->prev)
		pos->prev->next = node;
	pos->prev = node;
	if (pos == list->first)
		list->first = node;
	list->size++;
	return 1;
}

void list_remove(List *list, Node *pos)
{
	if (!list || !pos)
		return;
	if (list->size == 1 && list->first == pos && list->last == pos)
	{
		free(pos);
		list->size--;
		list_make_empty(list);
		return;
	}
	if (pos->prev)
	{
		if (pos == list->last)
			list->last = pos->prev;
		pos->prev->next = pos->next;
	}
	if (pos->next)
	{
		if (pos == list->first)
			list->first = pos->next;
		pos->next->prev = pos->prev;
	}
	free(pos);
	list->size--;
}

int list_get_size(List *list)
{
	if (!list)
		return 0;
	return list->size;
}

int list_pop_front(List *list, int *out)
{
	Node *node = NULL;
	if (!list || !out || list->size == 0)
		return 0;
	if (list->size == 1 && list->first)
	{
		*out = list->first->value;
		free(list->first);
		list_make_empty(list);
		return 1;
	}
	node = list->first->next;
	if (!node)
		return 0;
	*out = list->first->value;
	free(list->first);
	node->prev = NULL;
	list->first = node;
	list->size--;
	return 1;
}

int list_pop_back(List *list, int *out)
{
	Node *node = NULL;
	if (!list || !out || list->size == 0)
		return 0;
	if (list->size == 1 && list->last)
	{
		*out = list->last->value;
		free(list->last);
		list_make_empty(list);
		return 1;
	}
	node = list->last->prev;
	if (!node)
		return 0;
	*out = list->last->value;
	free(list->last);
	node->next = NULL;
	list->last = node;
	list->size--;
	return 1;
}

void list_print(List *list)
{
	Node *node = NULL;
	if (!list || list->size == 0)
		return;
	node = list->first;
	while(node)
	{
		printf("%d ", node->value);
		node = node->next;
	}
	printf("\n");
}

void list_clear(List *list)
{
	Node *node = NULL;
	if (!list)
		return;
	while(list->last)
	{
		node = list->last->prev;
		free(list->last);
		list->last = node;
	}
	list_make_empty(list);
}
#include <stdio.h>
#include <stdlib.h>
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
	node = (Node *)malloc(sizeof(Node));
	if (!node)
		return 0;
	node->value = value;
	node->next = list->first;
	node->prev = NULL;
	list->first = node;
	/*if (!list->last)
		list->last = list->first;*/
	list->size++;
	return 1;
}

int list_push_back(List *list, int value)
{
	Node *node = NULL;
	if (!list)
		return 0;
	node = (Node *)malloc(sizeof(Node));
	if (!node)
		return 0;
	node->value = value;
	node->prev = list->last;
	node->next = NULL;
	list->last = node;
	/*if (!list->first)
		list->first = list->last;*/
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
	pos->next = node;
	list->size++;
	return 1;
}

void list_remove(List *list, Node *pos)
{
	Node *node = NULL;
	if (!list || !pos)
		return;
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
	list->size--;
}

int list_get_size(List *list)
{
	if (!list)
		return 0;
	return list->size;
}

void list_pop_front(List *list)
{
	Node *node = NULL;
	if (!list)
		return;
	node = list->first->next;
	free(list->first);
	node->prev = NULL;
	list->first = node;
	list->size--;
}

void list_pop_back(List *list)
{
	Node *node = NULL;
	if (!list)
		return;
	node = list->last->prev;
	free(list->last);
	node->next = NULL;
	list->last = node;
	list->size--;
}

void list_clear(List *list)
{
	Node *node = NULL;
	if (!list)
		return;
	if (!list->last)
		return;
	node = list->last->prev;
	while(node)
	{
		free(list->last);
		list->last = node;
		node = list->last->prev;
	}
	list->size = 0;
}
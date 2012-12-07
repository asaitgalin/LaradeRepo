#ifndef _LIST_H_
#define _LIST_H_

/* Tiny integer list. Written by Andrey Saitgalin */

struct NodeTag;

struct NodeTag
{
	int value;
	struct NodeTag *next;
	struct NodeTag *prev;
};

typedef struct NodeTag Node;

typedef struct 
{
	Node *first;
	Node *last;
	unsigned int size;
}List;

int list_push_front(List *list, int value);
int list_push_back(List *list, int value);
int list_pop_front(List *list, int *out);
int list_pop_back(List *list, int *out);
int list_insert_after(List *list, Node *pos, int value);
int list_insert_before(List *list, Node *pos, int value);
int list_get_size(List *list);
void list_clear(List *list);
void list_remove(List *list, Node *pos);
void list_make_empty(List *list);
void list_print(List *list);

#endif
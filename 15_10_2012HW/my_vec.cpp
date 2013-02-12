#include <stdio.h>
#include <stdlib.h>
#include "my_vec.h"

pmy_vec v_create(uint start_size)
{
	pmy_vec v = (my_vec *)malloc(sizeof(my_vec));
	if (v)	
	{
		v->data = (int *)malloc(start_size * sizeof(int));
		v->data_max_size = start_size;
		v->size = 0;
	}
	if (v && v->data)
		return v;
	return NULL;
}

pmy_vec v_create_2()
{
	return v_create(DEFAULT_SIZE);	
}

void v_grow(pmy_vec v)
{
	int *new_data;
	if (v->data_max_size == 0) 
		(v->data_max_size)++;
	new_data = (int *)realloc(v->data, 2 * v->data_max_size * sizeof(int));
	if (new_data != NULL)
	{	
		v->data = new_data;
		v->data_max_size *= 2;
	}
}

void v_pushback(pmy_vec v, int value)
{
	if (!v) return;
	if (v->size + 1 == v->data_max_size)
		v_grow(v);
	v->data[v->size++] = value;
}

int v_popback(pmy_vec v)
{
	int value = v_at(v, v_size(v) - 1);
	if (value != -1)
	{
		v->size--;
		return value;
	}
	return -1;
}

int v_size(pmy_vec v)
{
	if (!v)
		return -1;
	return (v->size);
}

int v_empty(pmy_vec v)
{
	return (v_size(v) == 0);
}

int v_at(pmy_vec v, uint i)
{
	if (v)
		if (i < v->size)
			return (v->data[i]);
	return -1;
}

int v_front(pmy_vec v)
{
	return v_at(v, 0);
}

int v_back(pmy_vec v)
{
	return v_at(v, v_size(v) - 1);
}

int v_capacity(pmy_vec v)
{
	if (v)
		return (v->data_max_size);
	return 0;
}

void v_free(pmy_vec v)
{
	if (v)
	{
		if (v->data)
			free(v->data);
		free(v);
	}
}

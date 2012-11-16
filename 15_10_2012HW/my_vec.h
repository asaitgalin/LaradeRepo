#ifndef _MYVEC_H_
  #define _MYVEC_H_

/* My own small integer vector for pure C :) */

#define DEFAULT_SIZE 10

typedef unsigned uint;

typedef struct
{
	int *data;
	uint size;
	uint data_max_size;
}my_vec, *pmy_vec;

pmy_vec v_create(uint start_size);
pmy_vec v_create_2();
void v_grow(pmy_vec v);
void v_pushback(pmy_vec v, int value);
int v_popback(pmy_vec v);
int v_size(pmy_vec v);
int v_empty(pmy_vec v);
int v_at(pmy_vec v, uint i);
int v_front(pmy_vec v);
int v_back(pmy_vec v);
int v_capacity(pmy_vec v);
void v_free(pmy_vec v);

#endif
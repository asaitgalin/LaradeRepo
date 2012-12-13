#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 10
#define NUM 1000
#define BLOCKS_NUM NUM / BLOCK_SIZE

#define STACK_START_SIZE	10
#define STACK_GROW_RATE		2
#define STACK_REDUCE_RATE	4

typedef unsigned short size_t1;
//typedef size_t size_t1;

struct Stack
{
	int *arr;
	size_t1 pointer;
	//size_t1 size;
};

typedef Stack* pStack;

int result;

void PushStack(pStack p, int value)
{
	if (!p->arr)
	{
		p->arr = static_cast<int*>(calloc(STACK_START_SIZE, sizeof(int)));
		p->pointer = 1;
		p->arr[0] = STACK_START_SIZE;
	}

	p->arr[p->pointer] = value;
	++p->pointer;

	if (p->pointer == p->arr[0])
	{
		p->arr = static_cast<int*>(realloc(p->arr, p->arr[0] * STACK_GROW_RATE * sizeof(int)));
		p->arr[0] *= STACK_GROW_RATE;
	}
}

void PopStack(pStack p)
{
	result = p->arr[--p->pointer];
	if (p->pointer < p->arr[0] / STACK_REDUCE_RATE && p->arr[0]  >= STACK_START_SIZE * STACK_REDUCE_RATE)
	{
		p->arr = static_cast<int*>(realloc(p->arr, p->arr[0] / STACK_REDUCE_RATE * sizeof(int)));
		p->arr[0] /= STACK_REDUCE_RATE;
	}
}

void DeleteStack(pStack& p)
{
	delete p->arr;
	p->arr = NULL;
	delete p;
	p = NULL;
}

void CreateStack(pStack& p)
{
	p = new Stack();
	p->arr = NULL;
}

struct DinArray
{
	pStack **arr;
};

typedef DinArray* pArr;
pArr vector;

void InitArray()
{
	vector = new DinArray();
	vector->arr = static_cast<pStack**>(calloc(BLOCKS_NUM, sizeof(pStack*)));
}

void DeleteArray()
{
	for(size_t1 i=0; i < BLOCKS_NUM; ++i)
		if (vector->arr[i])
		{
			for(size_t1 j=0; j < BLOCK_SIZE; ++j)
				delete vector->arr[i][j];
			delete vector->arr[i];
		}
	delete vector->arr;
	delete vector;
}


void Push(size_t1 index, int value)
{
	unsigned char block = index / BLOCK_SIZE;
	unsigned char shift = index % BLOCK_SIZE;
	if (!vector->arr[block])
		vector->arr[block] = static_cast<pStack*>(calloc(BLOCK_SIZE, sizeof(pStack)));
	if (!vector->arr[block][shift])
		CreateStack(vector->arr[block][shift]);
	PushStack(vector->arr[block][shift], value);
}

void Pop(size_t1 index)
{
	unsigned char block = index / BLOCK_SIZE;
	unsigned char shift = index % BLOCK_SIZE;
	PopStack(vector->arr[block][shift]);
	bool flag = false;
	if (vector->arr[block][shift]->pointer == 1)
	{
		flag = true;
		DeleteStack(vector->arr[block][shift]);
	}

	if (!flag)
		return;

	for(size_t1 i=0; i < BLOCK_SIZE && flag; ++i)
		flag = flag && vector->arr[block][i] == NULL;
	if (flag)
	{
		delete vector->arr[block];
		vector->arr[block] = NULL;
	}
}

int main()
{
	freopen("C:\\temp\\input.txt", "r", stdin);
	InitArray();
	int n, num, k;
	char s[5];
	scanf("%d", &n);
	for(size_t i=0; i < n; ++i)
	{
		scanf("%5s", &s);
		scanf("%d", &num);
		--num;
		if (s[1] == 'U')
		{
			scanf("%d", &k);
			Push(num, k);
		}
		else
		{
			Pop(num);
			printf("%d\n", result);
		}
	}

	DeleteArray();
	return 0;
}
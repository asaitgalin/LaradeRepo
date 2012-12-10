#include <stack>

#define BLOCK_SIZE 10
#define NUM 1000
#define BLOCKS_NUM NUM / BLOCK_SIZE

typedef std::stack<int>* pStack;
typedef std::stack<int> Stack;

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
	for(size_t i=0; i < BLOCKS_NUM; ++i)
		if (vector->arr[i])
		{
			for(size_t j=0; j < BLOCK_SIZE; ++j)
				delete vector->arr[i][j];
			delete [] vector->arr[i];
		}
	delete [] vector->arr;
	delete vector;
}


void Push(size_t index, int value)
{
	size_t block = index / BLOCK_SIZE;
	size_t shift = index % BLOCK_SIZE;
	if (!vector->arr[block])
		vector->arr[block] = static_cast<pStack*>(calloc(BLOCK_SIZE, sizeof(pStack)));
	if (!vector->arr[block][shift])
		vector->arr[block][shift] = new Stack();
	vector->arr[block][shift]->push(value);
}

int Pop(size_t index)
{
	size_t block = index / BLOCK_SIZE;
	size_t shift = index % BLOCK_SIZE;
	int result = vector->arr[block][shift]->top();
	vector->arr[block][shift]->pop();
	bool flag = false;
	if (vector->arr[block][shift]->size() == 0)
	{
		flag = true;
		delete vector->arr[block][shift];
		vector->arr[block][shift] = NULL;
	}

	if (!flag)
		return result;

	for(size_t i=0; i < BLOCK_SIZE; ++i)
		flag = flag && vector->arr[block][i] != NULL;
	if (flag)
	{
		delete vector->arr[block];
		vector->arr[block] = NULL;
	}
	return result;
}

int main()
{
	//freopen("C:\\temp\\in.txt", "r", stdin);
	InitArray();
	int n, num, k;
	char s[10];
	scanf("%d", &n);
	for(size_t i=0; i < n; ++i)
	{
		scanf("%s", &s);
		scanf("%d", &num);
		if (!strcmp(s, "PUSH"))
		{
			scanf("%d", &k);
			Push(num, k);
		}
		else
		{
			k = Pop(num);
			printf("%d\n", k);
		}
	}

	DeleteArray();
	return 0;
}
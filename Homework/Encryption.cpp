#include <iostream>
#include <string>
#include <time.h>

#define TREE_TYPE char

struct ImplicityTreap
{
	int y;
	size_t size;
	TREE_TYPE c;
	ImplicityTreap* Left;
	ImplicityTreap* Right;

	ImplicityTreap(TREE_TYPE v)
	{
		this->c = v;
		y = rand();
		Left = 0;
		Right = 0;
		size = 1;
	}
};

typedef ImplicityTreap* pTreap;

size_t SizeOf(pTreap t)
{
	return t ? t->size : 0;
}

void Recalc(pTreap t)
{
	if (!t)
		return;
	t->size = SizeOf(t->Left) + SizeOf(t->Right) + 1;
}

pTreap Merge(pTreap l, pTreap r)
{
	if (!l)
		return r;
	if (!r)
		return l;
	pTreap result;

	if (l->y >= r->y)
	{
		result = l;
		result->Right = Merge(l->Right, r);
	}
	else
	{
		result = r;
		result->Left = Merge(l, r->Left);
	}
	Recalc(result);
	return result;
}

void Split(pTreap t, size_t x, pTreap& l, pTreap& r)
{
	if (!t)
	{
		l = 0;
		r = 0;
		return;
	}

	size_t curIndex = SizeOf(t->Left) + 1;
	if (curIndex <= x)
	{
		l = t;
		Split(t->Right, x-curIndex, l->Right, r);
		Recalc(l);
	}
	else
	{
		r = t;
		Split(t->Left, x, l, r->Left);
		Recalc(r);
	}
}

void PushBack(pTreap& t, TREE_TYPE v)
{
	pTreap p = new ImplicityTreap(v);
	t = Merge(t, p);
}

//#define PRINT_SIZES
void PrintRecursive(pTreap t)
{
	if (!t)
		return;
	PrintRecursive(t->Left);
#ifdef PRINT_SIZES
	std::cout << "(" << t->c << "," << t->size << ") ";
#else
	std::cout << t->c;
#endif
	PrintRecursive(t->Right);
}

void Print(pTreap t)
{
	PrintRecursive(t);
	std::cout << std::endl;
}

void DeleteTree(pTreap t)
{
	if (!t)
		return;
	DeleteTree(t->Left);
	DeleteTree(t->Right);
	delete t;
}

void Encrypt(pTreap& t, size_t L, size_t R, size_t s)
{
	pTreap l1, l2, l3, r;
	Split(t, L, l1, r);
	Split(r, R-L+1-s, l2, r);
	Split(r, s, l3, r);
	t = Merge(l1, l3);
	t = Merge(t, l2);
	t = Merge(t, r);
}

int main()
{
	srand(time(NULL));
	freopen("C:\\temp\\in.txt", "r", stdin);
	pTreap t = 0;
	std::string st;
	std::cin >> st;
	t = new ImplicityTreap(st[0]);
	for(size_t i=1; i < st.size(); ++i)
		PushBack(t, st[i]);
	int N;
	int l, r, s;
	std::cin >> N;
	for(size_t i=0; i < N; ++i)
	{
		std::cin >> l;
		std::cin >> r;
		std::cin >> s;
		Encrypt(t, l-1, r-1, s);
	}
	Print(t);
	DeleteTree(t);
	return 0;
}
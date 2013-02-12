#ifndef SORT_H
  #define SORT_H

#define SWAP(a, b) { int t = a; a = b; b = t; }

typedef int (*p_compare)(const void *a, const void *b);
void isort(void *a, size_t num, size_t item_size, p_compare cmp);
void qisort(void *a, size_t num, size_t item_size, p_compare cmp);

int bin_search(int *a, int n, int elem);
void bubble_sort(int *a, int n);
void insertion_sort(int *a, int n);
void quick_sort(int *a, int n);
void merge_sort(int *a, int n);
void heap_sort(int *a, int n);
float heap_sum(float *a, int n);

#endif
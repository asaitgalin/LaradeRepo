#ifndef _SORT_H_
  #define _SORT_H_

#define SWAP(a, b) { int t = a; a = b; b = t; }

int bin_search(int *a, int n, int elem);
void bubble_sort(int *a, int n);
void insertion_sort(int *a, int n);
void quick_sort(int *a, int n);
void merge_sort(int *a, int n);
void heap_sort(int *a, int n);
float heap_sum(float *a, int n);

#endif
#ifndef _SORT_H_
  #define _SORT_H_

#define SWAP(a, b) { int t = a; a = b; b = t; }

void insertion_sort(int *a, int n);
void quick_sort(int *a, int n);
void merge_sort(int *a, int n);
void heap_sort(int *a, int n);
float heap_sum(float *a, int n);

#endif
#pragma once
#include <stdbool.h>

typedef struct tuple_three_int{
    int left;
    int right;
    int sum;
}tuple_3i;

void swap(int *a, int *b);
int* bin_search_ptr(int *A, int size, int find);
bool bin_search_bool(int *A, int size, int find);
tuple_3i find_max_subarr(int *A, int size);
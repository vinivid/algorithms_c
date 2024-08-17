#include "actors.h"
#include <stdbool.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int* bin_search_ptr(int *A, int size, int find){
    int m;
    int start = 0;
    int end = size;

    while(start <= end){
        m = (start+end)/2;

        if(A[m] == find){
            return &A[m];
        }else if(find > A[m]){
            start = m+1;
        }else{
            end = m-1;
        }
    }

    return NULL;
}

bool bin_search_bool(int *A, int size, int find){
    int m;
    int start = 0;
    int end = size;

    while(start <= end){
        m = (start+end)/2;

        if(A[m] == find){
            return true;
        }else if(find > A[m]){
            start = m+1;
        }else{
            end = m-1;
        }
    }

    return false;
}

tuple_3i find_max_subarr(int *A, int size){
    tuple_3i tmp;
    tmp.sum = A[0];
    tmp.left = 0;
    tmp.right = 0;
    int current_left = 0;
    int curr_sum = A[0];

    for(int i = 1; i < size; ++i){
        curr_sum += A[i];

        if(curr_sum > tmp.sum){
            tmp.left = current_left;
            tmp.sum = curr_sum;
            tmp.right = i;
        }

        if(curr_sum < 0){
            current_left = i + 1;
            curr_sum = 0;
        }
    }

    return tmp;
}
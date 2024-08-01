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
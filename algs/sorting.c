#include "sorting.h"
#include "actors.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//TODO implementar em todas as funções pointeiros para funçoes para especificar ordem

void bubble_sort(int *A, int size){
    bool swaped = false;

    do{
        swaped = false;

        for(int i = 0; i < size - 1; ++i){
            if(A[i] > A[i+1]){
                swap(&A[i], &A[i+1]);
                swaped = true;
            }
        }

        size -= 1;
    }while(swaped == true);
}

void insert_sort(int *A, int size){
    int i;
    int comp;

    for(int j = 1; j < size; j++){
        comp = A[j];
        i = j - 1;

        while(A[i] > comp  && i > -1){
            A[i + 1] = A[i];
            --i;
        }

        A[i+1] = comp;
    }
}

void merge(int *A, int start, int middle, int end, int *B){
    int i = start;
    int j = middle;                  

    for(int k = start; k < end; ++k){
        if(i < middle && (j >= end || A[i] <= A[j])){
            B[k] = A[i];
            ++i;
        }else{
            B[k] = A[j];
            ++j;
        }
    }

    for(int k = start; k < end; ++k) A[k] = B[k];
}

void merge_sort(int *A, int size){
    int *B = (int *)malloc(size * sizeof(int));
    if(B == NULL){
        printf("ERRO: ALOCACAO DE MEMORIA FALHOU\n");
        exit(EXIT_FAILURE);        
    }

    for(int i = 0; i < size; ++i) B[i] = A[i];

    for(int i = 2; i < size*2; i *=2){
        int middle = 0;
        int end = 0;

        for(int j = 0; j < size; j += i){
            end = j+i;
            middle = (j + end)/2;
            if(end > size) end -= end-size;      

            merge(A, j, middle, end, B);
        }
    }

    free(B); B = NULL; 
}
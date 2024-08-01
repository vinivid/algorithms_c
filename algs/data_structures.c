#include "data_structures.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int construct_vec_i(vector_int *vec, int size){
    if(vec < 0){
        printf("\n\nERRO: TAMANHO NEGATIVO EM VETOR\n\n");
        return 1;
    }

    vec->size = size;
    vec->capacity = size;
    vec->elem = (int *)malloc(size * sizeof(int));
    vec->end_ptr = vec->elem + vec->size;
    vec->mem_end_ptr = vec->elem + vec->capacity;

    if(vec->elem == NULL){
        printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
        return 1;
    }
    return 0;
}

void init_vec_i(vector_int *vec, int val){
    for(int i = 0; i < vec->size; ++i){
        vec->elem[i] = val;
    }
}

void destroy_vec_i(vector_int *vec){
    free(vec->elem);
    vec->elem = NULL;
    vec->end_ptr = NULL;
    vec->mem_end_ptr = NULL;
}

bool is_empty_i(vector_int *vec){
    return vec->size == 0 ? true:false;
}

void resize_i(vector_int *vec, int val){
    vec->size = val;
    vec->end_ptr = vec->elem + val;
    vec->mem_end_ptr = vec->elem + vec->capacity;
}

int push_back_i(int val, vector_int *vec){
    if(vec->size == 0){
        vec->size = 1;
        vec->capacity = 1;
        vec->elem = (int *)malloc(sizeof(int));
        vec->end_ptr = vec->elem+vec->size;
        vec->mem_end_ptr = vec->elem+vec->capacity;

        if(vec->elem == NULL){
            printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
            return 1;
        }

        vec->elem[0] = val;
    }else if(vec->end_ptr >= vec->mem_end_ptr){
        ++vec->size;
        vec->capacity *= 2;
        vec->elem = realloc(vec->elem, vec->capacity*sizeof(int));

        if(vec->elem == NULL){
            printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
            return 1;
        }

        vec->end_ptr = vec->elem + vec->size;
        vec->mem_end_ptr = vec->elem + vec->capacity;
        
        *(vec->end_ptr-1) = val;
        ++vec->end_ptr;
    }else{
        vec->size += 1;
        *(vec->end_ptr-1) = val;
        ++vec->end_ptr;
    }

    return 0;
}

void pop_back_i(vector_int *vec){
    --vec->size;
    --vec->end_ptr;
}

int shrink_to_fit_i(vector_int *vec){
    vec->capacity = vec->size;
    vec->elem = realloc(vec->elem, vec->size*sizeof(int));
    if(vec->elem == NULL){
        printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
        return 1;
    }

    vec->end_ptr = vec->elem + vec->size;
    vec->mem_end_ptr = vec->end_ptr;
    return 0;
}

int erase_vec_i(vector_int *vec, int* element){    
    int *tmp = (int *)malloc(vec->capacity * sizeof(int));
    if(tmp == NULL){
        printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
        return 1;
    }

    int left = (int)(element - vec->elem);

    for(int i = left -1; i > -1; --i){
        tmp[i] = vec->elem[i];
    }

    for(int i = left+1; i < vec->size; ++i){
        tmp[i - 1] = vec->elem[i];  
    }

    free(vec->elem);
    vec->elem = tmp;
    vec->size -= 1;
    vec->end_ptr = vec->elem + vec->size;
    vec->mem_end_ptr = vec->elem + vec->capacity;

    return 0;
}
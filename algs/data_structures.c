#include "data_structures.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
/////////////////////////////////////
            Vetor amortizado
////////////////////////////////////
*/

vector_int construct_vec_i(int size){
    vector_int vec;
    if(size < 0){
        printf("\n\nERRO: TAMANHO NEGATIVO EM VETOR\n\n");
        vec.elem = NULL;
        vec._private_end_ptr = NULL;
        vec._private_mem_end_ptr = NULL;
        return vec;
    }

    if(size == 0){
        vec.elem = NULL;
        vec._private_end_ptr = NULL;
        vec._private_mem_end_ptr = NULL;

        return vec;
    }

    vec.elem = (int *)malloc(size * sizeof(int));
    vec._private_end_ptr = vec.elem + size;
    vec._private_mem_end_ptr = vec.elem + size;

    if(vec.elem == NULL){
        printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
        vec.elem = NULL;
        vec._private_end_ptr = NULL;
        vec._private_mem_end_ptr = NULL;
        return vec;
    }
    return vec;
}

void init_vec_i(vector_int *vec, int val){
    for(int i = 0; i < vec->_private_end_ptr - vec->elem; ++i){
        vec->elem[i] = val;
    }
}

int size_vec_i(vector_int *vec){
    return (int)((vec->_private_end_ptr) - vec->elem);
}

int capacity_vec_i(vector_int *vec){
    return (int)((vec->_private_mem_end_ptr) - vec->elem);
}

void destroy_vec_i(vector_int *vec){
    free(vec->elem);
    vec->elem = NULL;
    vec->_private_end_ptr = NULL;
    vec->_private_mem_end_ptr = NULL;
}

bool is_empty_vec_i(vector_int *vec){
    return vec->elem == vec->_private_end_ptr ? true:false;
}

void resize_vec_i(vector_int *vec, int val){
    vec->_private_end_ptr = vec->elem + (val+1);
}

int push_back_vec_i(int val, vector_int *vec){
    if(vec->_private_end_ptr - vec->elem == 0){
        vec->elem = (int *)malloc(sizeof(int));

        if(vec->elem == NULL){
            printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
            return 1;
        }

        vec->_private_end_ptr = vec->elem + 1;
        vec->_private_mem_end_ptr = vec->elem + 1;

        vec->elem[0] = val;

        return 0;
    }else if(vec->_private_end_ptr >= vec->_private_mem_end_ptr){
        int size = (int)(vec->_private_end_ptr - vec->elem);
        int capacity = (int)(vec->_private_mem_end_ptr - vec->elem) * 2;
        vec->elem = realloc(vec->elem, capacity * sizeof(int));

        if(vec->elem == NULL){
            printf("\n\nERRO: RELOCACAO DE MEMORIA FALHOU\n\n");
            return 2;
        }

        vec->_private_end_ptr = vec->elem + size;
        vec->_private_mem_end_ptr = vec->elem + capacity;
        *vec->_private_end_ptr = val;
        ++vec->_private_end_ptr;

        return 0;
    }else{
        *vec->_private_end_ptr = val;
        ++vec->_private_end_ptr;

        return 0;
    }
}

void pop_back_vec_i(vector_int *vec){
    --vec->_private_end_ptr;
}

int shrink_to_fit_vec_i(vector_int *vec){
    int new_size = (int)(vec->_private_end_ptr - vec->elem); 
    vec->elem = realloc(vec->elem, new_size * sizeof(int));
    if(vec->elem == NULL){
        printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
        return 1;
    }

    vec->_private_end_ptr = vec->elem + new_size;
    vec->_private_mem_end_ptr = vec->_private_end_ptr;
    return 0;
}

int erase_vec_i(vector_int *vec, int* element){
    int size = (int)(vec->_private_end_ptr - vec->elem);
    int capacity = (int)(vec->_private_mem_end_ptr - vec->elem);    
    int *tmp = (int *)malloc( capacity * sizeof(int));
    if(tmp == NULL){
        printf("\n\nERRO:: ALOCACAO DE MEMORIA FALHOU\n\n");
        return 1;
    }

    int left = (int)(element - vec->elem);

    for(int i = left -1; i > -1; --i){
        tmp[i] = vec->elem[i];
    }

    for(int i = left+1; i < size; ++i){
        tmp[i - 1] = vec->elem[i];  
    }

    free(vec->elem);
    vec->elem = tmp;
    vec->_private_end_ptr = vec->elem + size-1;
    vec->_private_mem_end_ptr = vec->elem + capacity;
    return 0;
}

/*
/////////////////////////////////////////////////////
                    Stack
/////////////////////////////////////////////////////
*/

struct data_structure_stack_int{
    int *start;
    int *end;
    int *capacity;
};

stack_int* construct_stack_i() {
    stack_int *tmp = (stack_int *)malloc(sizeof(stack_int));
    tmp->start = NULL;
    tmp->end = NULL;
    tmp->capacity = NULL;

    return tmp;
}

void destroy_stack_i(stack_int *stck) {
    if(stck->start == NULL) return;

    free(stck->start);
}

int get_top_stack_i(stack_int *stck) {
    if(stck->start == stck->end){
        printf("\n\nERRO:: SEM VALOR NO TOPO PARA RETORNAR\n\n");
        return -451;
    }

    return *--stck->end;
}

int set_top_stack_i(int val, stack_int *stck) {
    if(stck->start == stck->end) {
        printf("\n\nERRO:: SEM VALOR NO TOPO PARA RETORNAR\n\n");
        return 1;
    }

    *--stck->end = val;
    return 0;
}

int push_back_stack_i(int val, stack_int *stck) {
    if(stck->start == stck->end) {
        stck->start = (int *)malloc(sizeof(int));

        if (stck->start == NULL) {
            printf("\n\nERRO:: ALOCACAO DE MEMORIA FALHOU\n\n");
            return 1;
        }

        stck->end = stck->start + 1;
        stck->capacity = stck->start +1;
        stck->start[0] = val;

        return 0;
    }else if(stck->end >= stck->capacity) {
        int size = (int)(stck->end - stck->start);
        int capacity = (int)(stck->capacity - stck->start) * 2;

        stck->start = realloc(stck->start, capacity * sizeof(int));

        if(stck->start == NULL) {
            printf("\n\nERRO:: REALOCACAO DE MEMORIA FALHOU\n\n");
            return 2;
        }

        stck->end = stck->start + size;
        stck->end = stck->start + capacity;

        *stck->end = val;
        ++stck->end;

        return 0;
    }else{
        *stck->end = val;
        ++stck->end;

        return 0;
    }
}

int pop_back_stack_i(stack_int *stck) {
    if(stck->end - stck->start) {
        --stck->end;
        return *(stck->end + 1);
    }else {
        printf("ERRO:: NAO HA ELEMENTOS PARA REMOVER");
        return -451;
    }
}

int size_stack_i(stack_int *stck){
    return (int)(stck->end - stck->start);
}

bool is_empty_stack_i(stack_int *stck){
    return stck->start == stck->end ? true:false;
}